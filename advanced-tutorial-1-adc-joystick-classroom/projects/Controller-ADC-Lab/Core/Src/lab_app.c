#include "lab_app.h"
#include "lab_tasks.h"
#include "adc.h"
#include "lcd/lcd.h"
#include <math.h>

/* Supplied display/lifetime scaffolding. ADC operations and the calculations
   belong to lab_tasks.c. Four independent samples are not an atomic frame. */
volatile uint16_t g_lab_samples[LAB_AXIS_COUNT] __attribute__((aligned(4)));
static bool preparation_done, dma_done;
static HAL_StatusTypeDef preparation_status, dma_status;
static const char *configuration_error;
static uint32_t last_update;

void LabApp_Init(void)
{
    preparation_status = HAL_ERROR;
    preparation_done = LabStudent_PrepareADC(&preparation_status);
    dma_done = false;
    configuration_error = 0;
#if LAB_STAGE != LAB_POLLING
    if (preparation_done && preparation_status == HAL_OK) {
        /* Prevent an invalid DMA handle or a wider transfer from corrupting RAM.
           Do not correct a student's IOC or restart a stopped transfer here. */
        if (!hadc1.DMA_Handle) {
            configuration_error = "DMA CONFIG TODO";
        } else if (hadc1.DMA_Handle->Init.MemDataAlignment != DMA_MDATAALIGN_HALFWORD ||
                   hadc1.DMA_Handle->Init.PeriphDataAlignment != DMA_PDATAALIGN_HALFWORD) {
            configuration_error = "DMA WIDTH CHECK";
        } else {
            dma_status = HAL_ERROR;
            dma_done = LabStudent_StartDMA(g_lab_samples, &dma_status);
        }
    }
#endif
    last_update = HAL_GetTick() - 100U;
}

static void DrawStatus(HAL_StatusTypeDef status)
{
    const char *text = status == HAL_TIMEOUT ? "ADC TIMEOUT" :
                       status == HAL_BUSY ? "ADC BUSY" : "ADC ERROR";
    tft_prints(0, 2, "%s", text);
}

static void DrawPolling(void)
{
    uint16_t raw = 0U;
    HAL_StatusTypeDef status = HAL_ERROR;
    if (!LabStudent_ReadPolling(&raw, &status)) {
        tft_prints(0, 2, "POLL READ TODO");
        return;
    }
    if (status != HAL_OK) { DrawStatus(status); return; }
    tft_prints(0, 2, "RAW:%4u", (unsigned)raw);
    uint32_t mv = 0U;
    if (LabStudent_ToMillivolts(raw, LAB_REFERENCE_MV, &mv))
        tft_prints(0, 3, "MV:%5u", (unsigned)mv);
    else
        tft_prints(0, 3, "VOLTAGE TODO");
    tft_prints(0, 5, "REF:%u mV", (unsigned)LAB_REFERENCE_MV);
    tft_prints(0, 6, "12-BIT 0..4095");
    tft_prints(0, 8, "PREDICT/MEASURE");
}

static bool DMAReady(void)
{
    if (configuration_error) { tft_prints(0, 2, "%s", configuration_error); return false; }
    if (!dma_done) { tft_prints(0, 2, "DMA START TODO"); return false; }
    if (dma_status != HAL_OK) { DrawStatus(dma_status); return false; }
    return true;
}

static void DrawDMA(void)
{
    if (!DMAReady()) return;
    for (unsigned i = 0; i < LAB_AXIS_COUNT; ++i)
        tft_prints(0, (uint8_t)(i + 2U), "BUF%u:%4u", i, (unsigned)g_lab_samples[i]);
    tft_prints(0, 7, "SCAN:%u DMA:%s", (unsigned)hadc1.Init.NbrOfConversion,
               hadc1.DMA_Handle->Init.Mode == DMA_CIRCULAR ? "C" : "N");
    tft_prints(0, 8, "MAP EACH AXIS");
}

static bool DrawAxis(uint8_t row, const char *name, uint16_t raw, float value, bool done)
{
    if (!done) { tft_prints(0, row, "%s:%4u TODO", name, (unsigned)raw); return false; }
    if (!isfinite(value) || value < -1.01f || value > 1.01f) {
        tft_prints(0, row, "%s:BAD MATH", name); return false;
    }
    /* Formatting only; this does not repair or clamp the student's calculation. */
    unsigned n = (unsigned)(fabsf(value) * 100.0f + 0.5f);
    tft_prints(0, row, "%s:%4u %c%u.%02u", name, (unsigned)raw,
               value < 0.0f ? '-' : '+', n / 100U, n % 100U);
    return true;
}

static void DrawExtent(uint8_t row, unsigned stick, float x, float y, bool axes_ready)
{
    float extent = 0.0f;
    if (!axes_ready) { tft_prints(0, row, "J%u PUSH:---", stick); return; }
    if (!LabStudent_StickExtent(x, y, &extent)) {
        tft_prints(0, row, "J%u PUSH:TODO", stick); return;
    }
    if (!isfinite(extent) || extent < 0.0f || extent > 1.01f) {
        tft_prints(0, row, "J%u PUSH:BAD", stick); return;
    }
    unsigned n = (unsigned)(extent * 100.0f + 0.5f);
    tft_prints(0, row, "J%u PUSH:%u.%02u", stick, n / 100U, n % 100U);
}

static void DrawCalibration(void)
{
    if (!DMAReady()) return;
    const unsigned index[4] = LAB_AXIS_INDICES;
    const uint16_t minimum[4] = LAB_MINIMA, centre[4] = LAB_CENTRES, maximum[4] = LAB_MAXIMA;
    const int direction[4] = LAB_AXIS_DIRECTIONS;
    const char *name[4] = {"J1X", "J1Y", "J2X", "J2Y"};
    const uint8_t row[4] = {1, 2, 5, 6};
    float value[4] = {0};
    bool ready[4] = {false};
    for (unsigned i = 0; i < 4; ++i) {
        if (index[i] >= LAB_AXIS_COUNT) { tft_prints(0, 1, "MAPPING CHECK"); return; }
        uint16_t raw = g_lab_samples[index[i]];
        bool done = LabStudent_NormalizeAxis(raw, minimum[i], centre[i], maximum[i],
                                             LAB_DEADBAND, &value[i]);
        value[i] *= (float)direction[i];
        ready[i] = DrawAxis(row[i], name[i], raw, value[i], done);
    }
    DrawExtent(3, 1U, value[0], value[1], ready[0] && ready[1]);
    DrawExtent(7, 2U, value[2], value[3], ready[2] && ready[3]);
    tft_prints(0, 8, "CALIBRATE/RETEST");
}

void LabApp_Update(void)
{
    uint32_t now = HAL_GetTick();
    if ((uint32_t)(now - last_update) < 100U) return;
    last_update = now;
    tft_prints(0, 0, "ADC LAB %c", 'A' + LAB_STAGE - 1);
    if (!preparation_done) tft_prints(0, 2, "PREPARE ADC TODO");
    else if (preparation_status != HAL_OK) DrawStatus(preparation_status);
    else {
        switch (LAB_STAGE) {
        case LAB_POLLING: DrawPolling(); break;
        case LAB_DMA: DrawDMA(); break;
        case LAB_CALIBRATION: DrawCalibration(); break;
        default: tft_prints(0, 2, "STAGE CONFIG BAD"); break;
        }
    }
    tft_prints(0, 9, "RUN:%u s", (unsigned)(now / 1000U));
    tft_update(0);
}

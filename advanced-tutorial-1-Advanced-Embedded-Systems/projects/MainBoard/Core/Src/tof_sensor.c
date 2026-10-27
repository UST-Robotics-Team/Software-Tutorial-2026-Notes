#include "sensors.h"
/* Add i2c.h after I2C2 code generation for TOF_Probe(). */
#include "tutorial_config.h"
#include "vl53l1x_subset.h"
#include "vl53l1_platform.h"
static bool initialized;
HAL_StatusTypeDef TOF_Probe(void)
{
    /* TODO TOF A: probe the shifted device address on generated I2C2.
       A successful address response does not establish a valid distance. */
    return HAL_ERROR;
}

HAL_StatusTypeDef TOF_Init(void)
{
    initialized=false;
    VL53L1_PlatformBegin();
    HAL_StatusTypeDef probe = TOF_Probe();
    if (probe != HAL_OK) return probe;
    uint32_t start=HAL_GetTick();
    uint8_t booted=0;
    while (!booted) {
        if (VL53L1X_BootState(TOF_ADDRESS_HAL,&booted)) return HAL_ERROR;
        if ((uint32_t)(HAL_GetTick()-start)>=500U) return HAL_TIMEOUT;
        HAL_Delay(2);
    }
    uint16_t id=0;
    if (VL53L1X_GetSensorId(TOF_ADDRESS_HAL,&id) || id!=0xEACCU) return HAL_ERROR;
    int8_t s=VL53L1X_SensorInit(TOF_ADDRESS_HAL);
    if (s) return s==-2 ? HAL_TIMEOUT : HAL_ERROR;
    /* Normalize the timing budget first: the mirrored default table's encoded
       budget is not recognized by its getter. SetDistanceMode preserves it. */
    if (VL53L1X_SetTimingBudgetInMs(TOF_ADDRESS_HAL,50) ||
        VL53L1X_SetDistanceMode(TOF_ADDRESS_HAL,2) ||
        VL53L1X_SetInterMeasurementInMs(TOF_ADDRESS_HAL,100) ||
        VL53L1X_StartRanging(TOF_ADDRESS_HAL)) return HAL_ERROR;
    initialized=true;
    return HAL_OK;
}
HAL_StatusTypeDef TOF_Read(TOF_Sample *sample)
{
    if (!sample) return HAL_ERROR;
    sample->distance_mm=0; sample->range_status=255; sample->valid=false;
    if (!initialized) return HAL_ERROR;
    VL53L1_PlatformBegin();
    /* TODO TOF C: wait for readiness with a 500 ms maximum, read range status
       and distance, then clear the sensor event. Preserve the first I/O error.
       Set valid only for normalized status 0 and a nonzero distance.
       On any I/O failure, clear the distance and mark initialization invalid. */
    initialized=false;
    return HAL_ERROR;
}

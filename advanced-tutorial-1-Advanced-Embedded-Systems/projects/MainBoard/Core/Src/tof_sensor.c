#include "sensors.h"
#include "i2c.h"
#include "tutorial_config.h"
#include "vl53l1x_subset.h"
#include "vl53l1_platform.h"
static bool initialized;
HAL_StatusTypeDef TOF_Init(void)
{
    initialized=false;
    VL53L1_PlatformBegin();
    if (HAL_I2C_IsDeviceReady(&hi2c2,TOF_ADDRESS_HAL,2,SENSOR_IO_TIMEOUT_MS)!=HAL_OK)
        return HAL_ERROR;
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
    uint32_t start=HAL_GetTick();
    uint8_t ready=0;
    while (!ready) {
        if (VL53L1X_CheckForDataReady(TOF_ADDRESS_HAL,&ready)) {
            initialized=false; return HAL_ERROR;
        }
        if ((uint32_t)(HAL_GetTick()-start)>=500U) {
            initialized=false; return HAL_TIMEOUT;
        }
        HAL_Delay(2);
    }
    if (VL53L1X_GetRangeStatus(TOF_ADDRESS_HAL,&sample->range_status) ||
        VL53L1X_GetDistance(TOF_ADDRESS_HAL,&sample->distance_mm) ||
        VL53L1X_ClearInterrupt(TOF_ADDRESS_HAL)) {
        sample->distance_mm=0; sample->range_status=255;
        initialized=false; return HAL_ERROR;
    }
    sample->valid=sample->range_status==0 && sample->distance_mm!=0;
    return HAL_OK;
}

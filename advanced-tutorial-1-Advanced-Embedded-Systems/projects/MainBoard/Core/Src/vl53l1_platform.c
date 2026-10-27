#include "vl53l1_platform.h"
#include "main.h"
/* Add i2c.h after enabling I2C2 and generating code in the TOF exercise. */
#include "tutorial_config.h"
/* One foreground sensor operation at a time; no ISR/RTOS callers. */
static int8_t first_error;
void VL53L1_PlatformBegin(void) { first_error=0; }
int8_t VL53L1_PlatformError(void) { return first_error; }
uint32_t VL53L1_PlatformTick(void) { return HAL_GetTick(); }
void VL53L1_PlatformDelay(uint32_t ms) { HAL_Delay(ms); }
static int8_t write_bytes(uint16_t dev, uint16_t reg, uint8_t *data, uint16_t n)
{
    if (first_error) return first_error;
    /* TODO TOF B: write n bytes with a 16-bit register address and timeout.
       Replace the placeholder status; keep the first-error guard. */
    (void)dev; (void)reg; (void)data; (void)n;
    HAL_StatusTypeDef status = HAL_ERROR;
    if (status != HAL_OK) first_error=-1;
    return first_error;
}
static int8_t read_bytes(uint16_t dev, uint16_t reg, uint8_t *data, uint16_t n)
{
    for (uint16_t i=0;i<n;++i) data[i]=0;
    if (first_error) return first_error;
    /* TODO TOF B: read n bytes with a 16-bit register address and timeout. */
    (void)dev; (void)reg;
    HAL_StatusTypeDef status = HAL_ERROR;
    if (status != HAL_OK) first_error=-1;
    return first_error;
}
int8_t VL53L1_WrByte(uint16_t dev,uint16_t reg,uint8_t v)
{ return write_bytes(dev,reg,&v,1); }
int8_t VL53L1_WrWord(uint16_t dev,uint16_t reg,uint16_t v)
{ uint8_t b[2]={(uint8_t)(v>>8),(uint8_t)v}; return write_bytes(dev,reg,b,2); }
int8_t VL53L1_WrDWord(uint16_t dev,uint16_t reg,uint32_t v)
{ uint8_t b[4]={(uint8_t)(v>>24),(uint8_t)(v>>16),(uint8_t)(v>>8),(uint8_t)v};
  return write_bytes(dev,reg,b,4); }
int8_t VL53L1_RdByte(uint16_t dev,uint16_t reg,uint8_t *v)
{ return read_bytes(dev,reg,v,1); }
int8_t VL53L1_RdWord(uint16_t dev,uint16_t reg,uint16_t *v)
{
    if (!v) { first_error=-1; return first_error; }
    uint8_t b[2] = {0};
    int8_t status = read_bytes(dev,reg,b,2);
    if (status) return status;
    /* TODO TOF B: combine b[0]/b[1] in the documented byte order into *v.
       Return zero only after implementing the conversion. */
    first_error=-1;
    return first_error;
}

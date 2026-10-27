#include "vl53l1_platform.h"
#include "i2c.h"
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
    if (HAL_I2C_Mem_Write(&hi2c2, dev, reg, I2C_MEMADD_SIZE_16BIT,
                         data,n,SENSOR_IO_TIMEOUT_MS)!=HAL_OK) first_error=-1;
    return first_error;
}
static int8_t read_bytes(uint16_t dev, uint16_t reg, uint8_t *data, uint16_t n)
{
    for (uint16_t i=0;i<n;++i) data[i]=0;
    if (first_error) return first_error;
    if (HAL_I2C_Mem_Read(&hi2c2, dev, reg, I2C_MEMADD_SIZE_16BIT,
                        data,n,SENSOR_IO_TIMEOUT_MS)!=HAL_OK) first_error=-1;
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
{ uint8_t b[2]; int8_t s=read_bytes(dev,reg,b,2); *v=((uint16_t)b[0]<<8)|b[1]; return s; }

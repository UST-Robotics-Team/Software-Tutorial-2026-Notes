#ifndef VL53L1_TUTORIAL_PLATFORM_H
#define VL53L1_TUTORIAL_PLATFORM_H
#include <stdint.h>
void VL53L1_PlatformBegin(void);
int8_t VL53L1_PlatformError(void);
uint32_t VL53L1_PlatformTick(void);
void VL53L1_PlatformDelay(uint32_t ms);
int8_t VL53L1_WrByte(uint16_t dev, uint16_t reg, uint8_t value);
int8_t VL53L1_WrWord(uint16_t dev, uint16_t reg, uint16_t value);
int8_t VL53L1_WrDWord(uint16_t dev, uint16_t reg, uint32_t value);
int8_t VL53L1_RdByte(uint16_t dev, uint16_t reg, uint8_t *value);
int8_t VL53L1_RdWord(uint16_t dev, uint16_t reg, uint16_t *value);
#endif

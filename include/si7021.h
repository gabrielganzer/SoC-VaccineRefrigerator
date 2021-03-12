#ifndef __si7021_H
#define __si7021_H
#ifdef __cplusplus
    extern "C" {
#endif

#include "stm32f4xx_hal.h"

#define SI7021_ADDRESS_READ          (0x40 << 1) | 0x01
#define SI7021_ADDRESS_WRITE         (0x40 << 1)
#define SI7021_A                      0x40
#define SI7021_B                      0x20

#define SI7021_MEASURE_TEMP_NOHOLD    0xF3 // Measure Temperature, No Hold Master Mode

// In case of something went wrong...
#define SI7021_MEASURE_FAILED            0xFFFF

// Starts temperature measurement. This blocking call takes about 20ms to complete.
// Params:
//  - `hi2c` I2C bus
// Returns current temperature in Celsius multiplied by 100 (to avoid float integers)
// e.g. `+23.12C` -> `2312`
// In case of error returns `SI7021_MEASURE_FAILED`
int32_t si7021_measure_temperature(I2C_HandleTypeDef *hi2c, uint8_t addr);

#ifdef __cplusplus
}
#endif
#endif
#ifndef __i2c_H
#define __i2c_H
#ifdef __cplusplus
    extern "C" {
#endif

#include "define.h"

I2C_HandleTypeDef i2cHandle;

void I2C_Config(void);

#ifdef __cplusplus
}
#endif
#endif
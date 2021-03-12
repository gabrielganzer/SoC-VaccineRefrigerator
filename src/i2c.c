#include "i2c.h"

void I2C_Config(void) {

    //Enable clock to I2C1
    __HAL_RCC_I2C1_CLK_ENABLE();

    //Regular definition of I2C1 handler
    i2cHandle.Instance = I2C1;
    i2cHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    i2cHandle.Init.ClockSpeed = 100000;
    i2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    i2cHandle.Init.DutyCycle = I2C_DUTYCYCLE_2;
    i2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
    i2cHandle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
    i2cHandle.Init.OwnAddress1 = 0;
    i2cHandle.Init.OwnAddress2 = 0;
    HAL_I2C_Init(&i2cHandle);

}

#include "si7021.h"

//Used by si7021_measure_temperature
static int32_t _read_and_convert_temperature(I2C_HandleTypeDef *hi2c, uint8_t addr)
{
  uint8_t si7021_buf[4];
  int res = HAL_I2C_Master_Receive(hi2c, (addr<<1)|0x01, si7021_buf, 2, 100);

  if (res != HAL_OK) {
    return SI7021_MEASURE_FAILED;
  }
  int64_t temp_code = (si7021_buf[0] << 8 | si7021_buf[1]) * 100;
  int64_t temp = 17572 * temp_code / 6553500 - 4685;

  if (temp > 12500 || temp < -4000) {
    return SI7021_MEASURE_FAILED;
  }

  return (int32_t)temp;
}

int32_t si7021_measure_temperature(I2C_HandleTypeDef *hi2c, uint8_t addr)
{
  uint8_t si7021_buf[4];
  si7021_buf[0] = SI7021_MEASURE_TEMP_NOHOLD;

  int res = HAL_I2C_Master_Transmit(hi2c, addr<<1, &si7021_buf[0], 1, 100);
  if (res != HAL_OK) {
    return SI7021_MEASURE_FAILED;
  }
  HAL_Delay(30);

  return _read_and_convert_temperature(hi2c, addr);
}
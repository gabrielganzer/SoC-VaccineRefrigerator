#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "define.h"

#define COOLING_PIN         GPIO_PIN_0 //GPIOB
#define ALARM_PIN           GPIO_PIN_1 //GPIOB
#define BUTTON_UP           GPIO_PIN_0 //GPIOC
#define BUTTON_DOWN         GPIO_PIN_1 //GPIOC
#define BUTTON_LEFT         GPIO_PIN_2 //GPIOC
#define BUTTON_RIGHT        GPIO_PIN_3 //GPIOC
#define BUTTON_OK           GPIO_PIN_4 //GPIOC
#define BUTTON_BACK         GPIO_PIN_5 //GPIOC
#define SENSOR_OPEN_CLOSED  GPIO_PIN_0 //GPIOA
#define UART_TX             GPIO_PIN_2 //GPIOA
#define UART_RX             GPIO_PIN_3 //GPIOA
#define I2C_SCL             GPIO_PIN_6 //GPIOB
#define I2C_SDA             GPIO_PIN_9 //GPIOB

GPIO_InitTypeDef GPIO_Alarm;
GPIO_InitTypeDef GPIO_OpenClosed;
GPIO_InitTypeDef GPIO_Button;
GPIO_InitTypeDef GPIO_UART;
GPIO_InitTypeDef GPIO_I2C;
GPIO_InitTypeDef GPIO_SPI;

void GPIO_Config(void);

extern void printMessage(id_type id);

#ifdef __cplusplus
}
#endif
#endif
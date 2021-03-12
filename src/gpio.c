#include "gpio.h"
	
void GPIO_Config(void){

  //Enable clock to GPIO Ports
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  //Initialize UART GPIO
  GPIO_UART.Pin = UART_TX | UART_RX;
  GPIO_UART.Mode = GPIO_MODE_AF_PP;
  GPIO_UART.Pull = GPIO_PULLUP;
  GPIO_UART.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_UART.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_UART);

  //Initialize I2C GPIO
  GPIO_I2C.Pin = I2C_SCL | I2C_SDA;
  GPIO_I2C.Mode = GPIO_MODE_AF_OD;
  GPIO_I2C.Pull = GPIO_PULLUP;
  GPIO_I2C.Speed = GPIO_SPEED_FAST;
  GPIO_I2C.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(GPIOB, &GPIO_I2C);

  //Initialize Buttons (for now, LEFT and RIGHT are not being used)
  GPIO_Button.Pin = BUTTON_UP | BUTTON_DOWN | BUTTON_LEFT | BUTTON_RIGHT | BUTTON_OK;
  GPIO_Button.Mode = GPIO_MODE_IT_FALLING;
  GPIO_Button.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_Button);
  GPIO_Button.Pin = BUTTON_BACK;
  HAL_GPIO_Init(GPIOA, &GPIO_Button);

  //Initialize Alarm & Cooling System - LEDs
  GPIO_Alarm.Pin = COOLING_PIN | ALARM_PIN;
  GPIO_Alarm.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Alarm.Pull = GPIO_NOPULL;
  GPIO_Alarm.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_Alarm);

  //Initialize Open/Closed Sensor - Button
  GPIO_OpenClosed.Pin = GPIO_PIN_0;
  GPIO_OpenClosed.Mode = GPIO_MODE_INPUT;
  GPIO_OpenClosed.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_OpenClosed);

  //Enable Interrupt for buttons
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

void EXTI0_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(BUTTON_UP);
}

void EXTI1_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(BUTTON_DOWN);
}

void EXTI2_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(BUTTON_LEFT);
}

void EXTI3_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(BUTTON_RIGHT);
}

void EXTI4_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(BUTTON_OK);
}

void EXTI9_5_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(BUTTON_BACK);
}

//IRQ Callback for buttons
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

  switch(state) {
    case INIT:
      /* State INIT:
        - Button UP/DOWN increment/decrement UART string
        - Button OK saves the threshold, and goes SYS
      */
      if(GPIO_Pin == BUTTON_UP)
        str++;
      else if (GPIO_Pin == BUTTON_DOWN)
        str--;
      else if (GPIO_Pin == BUTTON_OK) {
        threshold = str;
        str = 0;
        set = 1;
        printMessage(CLEAN);
        printMessage(SYS);
        state = SYS;
      }
    break;
    case SYS:
    case COOLING:
    case ALARM:
      /* State SYS/COOLING/ALARM:
        - Button OK goes to settings where threshold can be modified
      */
      if (GPIO_Pin == BUTTON_OK) {
        printMessage(CLEAN);
        printMessage(SETTINGS);
        str = threshold;
        state = SETTINGS;
      }
    break;
    case SETTINGS:
      /* State SYS/COOLING/ALARM:
        - Button UP/DOWN increment/decrement UART string
        - Button OK saves the threshold, and return to SYS
        - Button BACK return to SYS without saving
      */
      if(GPIO_Pin == BUTTON_UP)
        str++;
      else if (GPIO_Pin == BUTTON_DOWN)
        str--;
      else if (GPIO_Pin == BUTTON_OK) {
        threshold = str;
        str = 0;
        set = 1;
        printMessage(CLEAN);
        printMessage(SYS);
        state = SYS;
      } else if (GPIO_Pin == BUTTON_BACK) {
        str = 0;
        printMessage(CLEAN);
        printMessage(SYS);
        state = SYS;
      }
    break;
    default:
      // Error message
      if (GPIO_Pin == (BUTTON_OK || BUTTON_BACK || BUTTON_UP || BUTTON_DOWN)) {
        printMessage(CLEAN);
        printMessage(ERROR);
      }
    break;
  }
}
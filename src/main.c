#include "define.h"
#include "gpio.h"
#include "timer.h"
#include "i2c.h"
#include "si7021.h"
#include "uart.h"
#include "rtc.h"

int main(void) {

  //Default initialization
  HAL_Init();
  SystemClock_Config();
  GPIO_Config();
  TIMER_Config();
  I2C_Config();
  UART_Config();
  DMA_Config();
  RTC_Config();

  //System initialization
  printMessage(INIT);
  state = INIT;
  threshold = 0;
  set = 0;

	while(1) {
    //Main routine defined as an FSM
    switch (state) {
      // Initial state (Configuration)
      case INIT:
        printMessage(LIMIT);
      break;
      // Default (Display temperature)
      case SYS:
        temperature = getTemperature();
        checkDoor();
        if((open == 1) && (checkTemperature(temperature) == 0)) {
          printMessage(CLEAN);
          printMessage(SYS);
          printMessage(ALARM);
          state = ALARM;
        } else if((open == 0) && (checkTemperature(temperature) == 1)) {
          printMessage(CLEAN);
          printMessage(SYS);
          printMessage(COOLING);
          state = COOLING;
        } else if((open == 1) && (checkTemperature(temperature) == 1)){
          printMessage(CLEAN);
          printMessage(SYS);
          printMessage(SIMULTANEOUS);
          state = SIMULTANEOUS;
        } else {
          printMessage(TEMP);
        }
      break;
      // Colling system ON
      case COOLING:
        temperature = getTemperature();
        checkDoor();
        if((open == 1) && (checkTemperature(temperature) == 0)){
          printMessage(CLEAN);
          printMessage(SYS);
          printMessage(ALARM);
          state = ALARM;
        } else if((open == 0) && (checkTemperature(temperature) == 1)){
          printMessage(TEMP);
        } else if((open == 1) && (checkTemperature(temperature) == 1)){
          printMessage(CLEAN);
          printMessage(SYS);
          printMessage(SIMULTANEOUS);
          state = SIMULTANEOUS;
        } else {
          printMessage(CLEAN);
          printMessage(SYS);
          state = SYS;
        }
      break;
      // Door OPEN
      case ALARM:
        temperature = getTemperature();
        checkDoor();
        if((open == 1) && (checkTemperature(temperature) == 0)){
          printMessage(TEMP);
        } else if((open == 0) && (checkTemperature(temperature) == 1)){
          printMessage(CLEAN);
          printMessage(SYS);
          printMessage(COOLING);
          state = COOLING;
        } else if((open == 1) && (checkTemperature(temperature) == 1)){
          printMessage(CLEAN);
          printMessage(SYS);
          printMessage(SIMULTANEOUS);
          state = SIMULTANEOUS;
        } else {
          printMessage(CLEAN);
          printMessage(SYS);
          state = SYS;
        }
      break;
      // Cooling system ON & Door OPEN
      case SIMULTANEOUS:
        temperature = getTemperature();
        checkDoor();
        if((open == 1) && (checkTemperature(temperature) == 0)){
          printMessage(CLEAN);
          printMessage(SYS);
          printMessage(ALARM);
          state = ALARM;
        } else if((open == 0) && (checkTemperature(temperature) == 1)){
          printMessage(CLEAN);
          printMessage(SYS);
          printMessage(COOLING);
          state = COOLING;
        } else if((open == 1) && (checkTemperature(temperature) == 1)){
          printMessage(TEMP);
        } else {
          printMessage(CLEAN);
          printMessage(SYS);
          state = SYS;
        }
      break;
      // Modify temperature threshold
      case SETTINGS:
        checkTemperature(getTemperature());
        checkDoor();
        printMessage(LIMIT);
      break;
      // Error
      default:
        printMessage(CLEAN);
        printMessage(ERROR);
      break;
    }
	}
}

void SystemClock_Config(void) {

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void SysTick_Handler(void) {

  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
}

/*
  Function: void checkDoor(void)
  Parameters: none
  Return: void
    If door is OPEN
      + Initialize timer interrupt and start couting
      + After period elapsed and door still open, set the alarm
    Else
      + Stop timer
      + Turn off the alarm
*/
void checkDoor(void) {

  if(HAL_GPIO_ReadPin(GPIOA, SENSOR_OPEN_CLOSED) == GPIO_PIN_RESET) {
    HAL_TIM_Base_Start_IT(&tim2Handle);
  } else {
    HAL_TIM_Base_Stop_IT(&tim2Handle);
    HAL_GPIO_WritePin(GPIOB, ALARM_PIN, GPIO_PIN_RESET);
    open = 0;
  }
}


/*
  Function: uint8_t checkTemperature(float temperature)
  Parameters: float temperature
  Return: uint8_t flag (1 out of range, 0 otherwise)
    If current temperature >= threshold+error
      + Turn on cooling system
    Else
      + Turn off cooling system
*/
uint8_t checkTemperature(float temperature) {
  
  if(set) {
      if(temperature >= (threshold+0.5)) {
        HAL_GPIO_WritePin(GPIOB, COOLING_PIN, GPIO_PIN_SET);
        return 1;
      } else {
        HAL_GPIO_WritePin(GPIOB, COOLING_PIN, GPIO_PIN_RESET);
        return 0;
      }
  } else {
    return 0;
  }
}

/*
  Function: float getTemperature(void)
  Parameters: none
  Return: float temperature
    + Read temperature from 2 sensors
    + Compute the average temperature
    + Return value
      - si7021_measure_temperature returns Celsius multiplied by 100
      - Ex.: 2056 = 20.56 oC
*/
float getTemperature(void) {

  int32_t tempA, tempB;
  float meanTemp;

  tempA = si7021_measure_temperature(&i2cHandle, SI7021_A);
  tempB = si7021_measure_temperature(&i2cHandle, SI7021_B);
  meanTemp = (float)((tempA+tempB)/2);
  return (meanTemp/100);
}



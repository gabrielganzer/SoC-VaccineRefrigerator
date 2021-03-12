#ifndef __timer_H
#define __timer_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "define.h"

#define ALARM_PIN             GPIO_PIN_1

TIM_HandleTypeDef tim2Handle;

void TIMER_Config(void);

#ifdef __cplusplus
}
#endif
#endif
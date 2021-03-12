#ifndef __define_H
#define __define_H
#ifdef __cplusplus
    extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

typedef enum {INIT, SYS, COOLING, ALARM, SIMULTANEOUS, TEMP, LIMIT, SETTINGS, LOG, CLEAN} id_type;

id_type state;
int8_t str;
uint8_t set;
uint8_t open;
int8_t threshold;
int8_t day;
int8_t month;
int8_t year;
int8_t hour;
int8_t minute;
char txData[100];
float temperature;

void SystemClock_Config(void);
void Error_Handler(void);

uint8_t checkTemperature(float temperature);
void checkDoor(void);
float getTemperature(void);

#ifdef __cplusplus
}
#endif
#endif
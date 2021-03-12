#ifndef __rtc_H
#define __rtc_H
#ifdef __cplusplus
    extern "C" {
#endif

#include "define.h"

RTC_HandleTypeDef rtcHandle;
RTC_AlarmTypeDef rtcAlarm;
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

void RTC_Config(void);

#ifdef __cplusplus
}
#endif
#endif
#include"rtc.h"

void RTC_Config(void) {

	//Enable RTC clock
	__HAL_RCC_RTC_ENABLE();
	//RTC Configurations
	rtcHandle.Instance = RTC;
	rtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
	rtcHandle.Init.AsynchPrediv = 127;
	rtcHandle.Init.SynchPrediv = 255;
	rtcHandle.Init.OutPut = RTC_OUTPUT_DISABLE;
	HAL_RTC_Init(&rtcHandle);
	/* //Alarm Configurations
	rtcAlarm.Alarm = RTC_ALARM_A;
	rtcAlarm.AlarmTime.Hours = 0;
	rtcAlarm.AlarmTime.Minutes = 0;
	rtcAlarm.AlarmTime.Seconds = 10;
	rtcAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
	rtcAlarm.AlarmDateWeekDay = 1;
	HAL_RTC_SetAlarm_IT(&rtcHandle, &rtcAlarm, RTC_FORMAT_BIN);
	
	HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn); */
	
}
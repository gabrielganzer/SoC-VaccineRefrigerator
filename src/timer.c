#include "timer.h"

void TIMER_Config(void) {

    //Enable clock to Timer2
    __HAL_RCC_TIM2_CLK_ENABLE();

    //Define clock source
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&tim2Handle, &sClockSourceConfig);

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&tim2Handle, &sMasterConfig);

    //Timer Initialization
    tim2Handle.Instance = TIM2;
    tim2Handle.Init.Prescaler = 16000;
    tim2Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    tim2Handle.Init.Period = 1000;
    tim2Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    tim2Handle.Init.RepetitionCounter = 0;
    HAL_TIM_Base_Init(&tim2Handle);

    //Enable timer interrupt
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_IRQHandler(void) {

    HAL_TIM_IRQHandler(&tim2Handle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

    if (htim->Instance == TIM2) {
        //Turn on the alarm for door open
        HAL_GPIO_WritePin(GPIOB, ALARM_PIN, GPIO_PIN_SET);
        open = 1;
    }

}
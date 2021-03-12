#include "uart.h"

void UART_Config(void) {

    //Enable clock to UART2
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART2_CLK_ENABLE();

    //UART Configuration
    uartHandle.Instance = USART2;
    uartHandle.Init.BaudRate = 115200;
    uartHandle.Init.Mode = UART_MODE_TX_RX;
    uartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    uartHandle.Init.StopBits = UART_STOPBITS_1;
    uartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&uartHandle);
}

void DMA_Config(void) {

    //Enable clock to DMA
    __HAL_RCC_DMA1_CLK_ENABLE();

    dmaHandle.Instance = DMA1_Stream5;
    dmaHandle.Init.Channel = DMA_CHANNEL_4;
    dmaHandle.Init.Direction = DMA_PERIPH_TO_MEMORY;
    dmaHandle.Init.PeriphInc = DMA_PINC_DISABLE;
    dmaHandle.Init.MemInc = DMA_MINC_ENABLE;
    dmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    dmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    dmaHandle.Init.Mode = DMA_CIRCULAR;
    dmaHandle.Init.Priority = DMA_PRIORITY_LOW;
    dmaHandle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    HAL_DMA_Init(&dmaHandle);

    __HAL_LINKDMA(&uartHandle, hdmarx, dmaHandle);

    HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

}

void DMA1_Stream5_IRQHandler(void) {

    HAL_DMA_IRQHandler(&dmaHandle);
}

//Define messages printed throughout whole execution
void printMessage(id_type id) {

  switch(id) {
    case INIT:
      sprintf(txData, "*****      VARE - Vaccine Refrigerator     *****\n\n");
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
      sprintf(txData, "Welcome, please insert the storage temperature\n");
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
      sprintf(txData, "limit in degrees Celsius before starting.\n");
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
      sprintf(txData, "(UP/DOWN) Increment/decrement value\n");
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
      sprintf(txData, "(OK) Save \n\n");
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
    break;
    case SYS:
      sprintf(txData, "*****      VARE - Vaccine Refrigerator     *****\n\n");
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
      sprintf(txData, "Storage temperature: %d\n",threshold);
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
      sprintf(txData, "(OK) Modify storage temperature\n\n");
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
    break;
    case COOLING:
      sprintf(txData, "*****        COOLING SYSTEM TURNED ON      *****\n\n");
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
    break;
    case ALARM:
      sprintf(txData, "*****               DOOR OPEN              *****\n\n");
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
    break;
    case SIMULTANEOUS:
      sprintf(txData, "***** COOLING SYSTEM TURNED ON & DOOR OPEN *****\n\n");
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
    break;
    case TEMP:
      sprintf(txData, "Current temperature: %.2f\r", temperature);
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
    break;
    case SETTINGS:
      sprintf(txData, "*****      VARE - Vaccine Refrigerator     *****\n\n");
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
      sprintf(txData, "Temperature defined in degrees Celsius.\n");
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
      sprintf(txData, "(UP/DOWN) Increment/decrement value\n");
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
      sprintf(txData, "(BACK) Return without saving\n");
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
      sprintf(txData, "(OK) Save and return\n\n");
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
    break;
    case LIMIT:
      sprintf(txData, "Storage limit: %d          \r", str);
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
    break;
    case CLEAN:
      sprintf(txData, "%c%c%c%c",0x1B,0x5B,0x32,0x4A);
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
    break;
    default:
      sprintf(txData, "ERROR\r");
      HAL_UART_Transmit(&uartHandle, (uint8_t*)txData, strlen(txData), 10);
    break;
  }
}
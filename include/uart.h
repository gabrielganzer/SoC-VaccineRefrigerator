#ifndef __uart_H
#define __uart_H
#ifdef __cplusplus
    extern "C" {
#endif

#include "define.h"

UART_HandleTypeDef uartHandle;
DMA_HandleTypeDef dmaHandle;

void UART_Config(void);
void DMA_Config(void);
void printMessage(id_type id);

#ifdef __cplusplus
}
#endif
#endif
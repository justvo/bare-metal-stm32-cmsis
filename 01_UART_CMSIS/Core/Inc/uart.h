#ifndef UART_H_
#define UART_H_


#include "stm32f3xx.h"

void UART2_Init(void);

void USART2_IRQHandler(void);

void UART2_SendString(char* c);

uint8_t UART2_DataAvailable(void);

uint8_t UART2_ReadByte(void);


#endif /* UART_H_ */

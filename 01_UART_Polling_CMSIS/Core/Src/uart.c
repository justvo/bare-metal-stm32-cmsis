#include "uart.h"

#define BUF_SIZE 64 //the size of buffer must be equal to 2^n (2,4,8,16,32,64...)

static volatile uint8_t rx_buffer[BUF_SIZE];
static volatile uint16_t head = 0;
static volatile uint16_t tail = 0;

void UART2_Init(void) {

	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	USART2->BRR = 0x45;
	USART2->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);
	USART2->CR1 |= (USART_CR1_RXNEIE);
	NVIC_EnableIRQ(USART2_IRQn);
}

void USART2_IRQHandler(void) {
	if ((USART2->ISR) & USART_ISR_RXNE) {
		uint8_t data = (uint8_t) USART2->RDR;
		uint16_t next_head = (head + 1) & (BUF_SIZE - 1);

		if (next_head != tail) {
			rx_buffer[head] = data;
			head = next_head;
		}

	}
	if (USART2->ISR & USART_ISR_ORE) {
	    USART2->ICR |= USART_ICR_ORECF;
	}
}

uint8_t UART2_ReadByte(void){
	if(head == tail){
		return 0;
	}

	uint8_t byte = rx_buffer[tail];
	tail = (tail + 1) & (BUF_SIZE-1);
	return byte;
}

uint8_t UART2_DataAvailable(void) {
    return (head != tail);
}









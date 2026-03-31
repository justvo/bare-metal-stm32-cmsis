#include "uart.h"

#define RX_BUF_SIZE 64 //the size of buffer must be equal to 2^n (2,4,8,16,32,64...)
#define TX_BUF_SIZE 128 //the size of buffer must be equal to 2^n (2,4,8,16,32,64...)

static volatile uint8_t rx_buffer[RX_BUF_SIZE];
static volatile uint16_t rx_head = 0;
static volatile uint16_t rx_tail = 0;

static volatile uint8_t tx_buffer[TX_BUF_SIZE];
static volatile uint16_t tx_head = 0;
static volatile uint16_t tx_tail = 0;

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
		uint16_t next_head = (rx_head + 1) & (RX_BUF_SIZE - 1);

		if (next_head != rx_tail) {
			rx_buffer[rx_head] = data;
			rx_head = next_head;
		}

	}
	if (USART2->ISR & USART_ISR_ORE) {
		USART2->ICR |= USART_ICR_ORECF;
	}

	if ((USART2->CR1 & USART_CR1_TXEIE) && (USART2->ISR & USART_ISR_TXE)) {
		if (tx_head != tx_tail) {
			USART2->TDR = tx_buffer[tx_tail];
			tx_tail = (tx_tail + 1) & (TX_BUF_SIZE - 1);
		} else {
			USART2->CR1 &= ~USART_CR1_TXEIE;
		}
	}
}

uint8_t UART2_ReadByte(void) {
	if (rx_head == rx_tail) {
		return 0;
	}

	uint8_t byte = rx_buffer[rx_tail];
	rx_tail = (rx_tail + 1) & (RX_BUF_SIZE - 1);
	return byte;
}

uint8_t UART2_DataAvailable(void) {
	return (rx_head != rx_tail);
}

void UART2_SendString(char* str) {
	while (*str != '\0') {
		uint16_t next_head = (tx_head + 1) & (TX_BUF_SIZE - 1);

		if (next_head != tx_tail) {
			tx_buffer[tx_head] = (uint8_t) *str;
			tx_head = next_head;
			str++;
		} else {
			break;
		}
	}
	USART2->CR1 |= USART_CR1_TXEIE;
}


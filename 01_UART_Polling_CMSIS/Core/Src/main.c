#include "main.h"
#include "stm32f3xx.h"

int main(void) {

	uint8_t recived;

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	GPIOA->MODER &= ~GPIO_MODER_MODER5;
	GPIOA->MODER |= (GPIO_MODER_MODER5_0);

	GPIOA->MODER &= ~(GPIO_MODER_MODER2|GPIO_MODER_MODER3);
	GPIOA->MODER |= (GPIO_MODER_MODER2_1|GPIO_MODER_MODER3_1);


	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL2 | GPIO_AFRL_AFRL3);
	GPIOA->AFR[0] |= ((7 << GPIO_AFRL_AFRL2_Pos) | (7 << GPIO_AFRL_AFRL3_Pos));

	USART2->BRR = 0x45;
	USART2->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);

	while (1) {
		if ((USART2->ISR) & USART_ISR_RXNE) {
			recived = (uint8_t) USART2->RDR;

			if(recived == 0x31){
				GPIOA->BSRR = GPIO_BSRR_BS_5;
			}else if(recived == 0x30){
				GPIOA->BSRR = GPIO_BSRR_BR_5;
			}

			while (!(USART2->ISR & USART_ISR_TXE)) {
			};
			USART2->TDR = recived;

		};

	}

}


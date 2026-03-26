#include "echo_led_control.h"



static void LED_ON(void){
	GPIOA->BSRR = GPIO_BSRR_BS_5;
}

static void LED_OFF(void){
	GPIOA->BSRR = GPIO_BSRR_BR_5;
}

static void ECHO(uint8_t data){
	while (!(USART2->ISR & USART_ISR_TXE)) {
	}
		USART2->TDR = data;
}

void LED_ECHO_Control(uint8_t data){
	if(data == 0x31){
		LED_ON();
	} else if(data == 0x30){
		LED_OFF();

	}
	ECHO(data);

}

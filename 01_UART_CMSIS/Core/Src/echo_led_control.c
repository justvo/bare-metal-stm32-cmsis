#include "echo_led_control.h"



void LED_ON(void){
	GPIOA->BSRR = GPIO_BSRR_BS_5;
}

void LED_OFF(void){
	GPIOA->BSRR = GPIO_BSRR_BR_5;
}




#include "main.h"
#include "stm32f3xx.h"
#include "gpio.h"
#include "uart.h"
#include "echo_led_control.h"

int main(void) {

	GPIO_Init();
	UART2_Init();

	while (1) {
		if(UART2_DataAvailable()){
			uint8_t data = UART2_ReadByte();
			LED_ECHO_Control(data);
		}
	}
}


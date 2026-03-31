#include "main.h"
#include "stm32f3xx.h"
#include "gpio.h"
#include "uart.h"
#include "echo_led_control.h"

int main(void) {

	GPIO_Init();
	UART2_Init();
	UART2_SendString(" -> UART_2 IS READY\r\n");

	while (1) {
		if (UART2_DataAvailable()) {
			uint8_t data = UART2_ReadByte();
			char echo[2] = { data, '\0' };
			UART2_SendString(echo);

			switch (data) {
			case '1':
				LED_ON();
				UART2_SendString(" -> LED ON\r\n");
				break;
			case '0':
				LED_OFF();
				UART2_SendString(" -> LED OFF\r\n");
				break;
			default:
				UART2_SendString(" -> Unknown command!\r\n");
				break;
			}

		}
	}
}


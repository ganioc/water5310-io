/*
 * d1_uart.c
 *
 *  Created on: 2023 Feb 19
 *      Author: ruffman
 */

#include "at32f415_board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "task_conf.h"

uint8_t at_rx_buffer[64];
uint8_t at_rx_counter = 0;
uint8_t at_tx_buf[AT_RX_BUFFER_LEN];
uint16_t at_tx_buf_idx = 0, at_tx_buf_amount = 0;

extern SemaphoreHandle_t xRxISRMutex, xTxISRMutex;

void init_d1_uart()
{
	gpio_init_type gpio_init_struct;

	/* enable the usart2 and gpio clock */
	crm_periph_clock_enable(D1_UART_CRM_CLK, TRUE);
	crm_periph_clock_enable(D1_UART_TX_GPIO_CRM_CLK, TRUE);

	gpio_default_para_init(&gpio_init_struct);

	/* configure the usart2 tx pin */
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pins = D1_UART_TX_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOA, &gpio_init_struct);

	/* configure the usart2 rx pin */
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pins = D1_UART_RX_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(GPIOA, &gpio_init_struct);

	/* config usart nvic interrupt */
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
	nvic_irq_enable(D1_UART_IRQn, 2, 0);

	usart_init(D1_UART, 115200, USART_DATA_8BITS, USART_STOP_1_BIT);
	usart_transmitter_enable(D1_UART, TRUE);
	usart_receiver_enable(D1_UART, TRUE);

	/* enable usart2 interrupt */
	usart_interrupt_enable(D1_UART, USART_RDBF_INT, TRUE);
	usart_interrupt_enable(D1_UART, USART_IDLE_INT, FALSE);

	usart_enable(D1_UART, TRUE);
}

/**
 * @brief  this function handles usart3 handler.
 * @param  none
 * @retval none
 */
void USART1_IRQHandler(void)
{
	if (D1_UART->ctrl1_bit.rdbfien != RESET)
	{
		if (usart_flag_get(D1_UART, USART_RDBF_FLAG) != RESET)
		{
			/* read one byte from the receive data register */
			at_rx_buffer[at_rx_counter++] = usart_data_receive(D1_UART);

			//      at32_led_toggle(LED4);

			usart_interrupt_enable(D1_UART, USART_IDLE_INT, TRUE);
		}
		if (usart_flag_get(D1_UART, USART_IDLEF_FLAG) != RESET)
		{
			// copy rx buffer data out,
			//    	at32_led_toggle(LED3);
			if (at_rx_counter > 0)
			{

				update_at_rx_buf(at_rx_buffer, at_rx_counter);

				xSemaphoreGiveFromISR(xRxISRMutex, NULL);

				// usart2_rx_counter reset
				at_rx_counter = 0;
			}

			usart_interrupt_enable(D1_UART, USART_IDLE_INT, FALSE);
		}
	}

	if (D1_UART->ctrl1_bit.tdbeien != RESET)
	{
		if (usart_flag_get(D1_UART, USART_TDBE_FLAG) != RESET)
		{
			/* write one byte to the transmit data register */
			usart_data_transmit(D1_UART, at_tx_buf[at_tx_buf_idx++]);

			if (at_tx_buf_idx == at_tx_buf_amount)
			{
				/* disable the usart2 transmit interrupt */
				usart_interrupt_enable(D1_UART, USART_TDBE_INT, FALSE);
				xSemaphoreGiveFromISR(xTxISRMutex, NULL);
			}
		}
	}
}

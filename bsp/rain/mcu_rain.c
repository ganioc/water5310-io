/*
 * mcu_rain.c
 *
 *  Created on: 2023 Feb 24
 *      Author: ruffman
 */
#include "at32f415_board.h"
#include "task_conf.h"

#include <string.h>


uint32_t rain_count = 0;
uint32_t pulse_count = 0;

enum RAIN_MODE   rain_mode = RAIN_MODE_QUERY;
enum RAIN_MODE   pulse_mode = RAIN_MODE_QUERY;

//char temp_rain[32];

extern enum RAINDROP_STATE  raindrop_state;
extern enum RAINDROP_STATE  pulse_state;


uint8_t get_rain_mode(uint8_t channel){
	if(channel == 1){
		return (uint8_t)rain_mode;
	}else{
		return (uint8_t)pulse_mode;
	}
}

void set_rain_mode(uint8_t channel, uint8_t mode){
	if(channel == 1){
		if(mode == 0){
			rain_mode = RAIN_MODE_QUERY;
			// save_rain_state(0);
		}else{
			rain_mode = RAIN_MODE_NOTIFY;
			// save_rain_state(1);
		}
	}else{
		if(mode == 0){
			pulse_mode = RAIN_MODE_QUERY;
			// save_rain_state(0);
		}else{
			pulse_mode = RAIN_MODE_NOTIFY;
			// save_rain_state(1);
		}
	}

}

uint32_t get_rain_count(uint8_t channel){
	if(channel == 1){
		return rain_count;
	}else{
		return pulse_count;
	}

}
void set_rain_count(uint8_t channel, uint32_t count){
	if(channel == 1){
		rain_count = count;
	}else{
		pulse_count = count;
	}

}

void init_rain_gpio(){
	init_gpio_input(
			RAIN_CRM_CLOCK,
			RAIN_PORT,
			RAIN_PIN,
			GPIO_PULL_UP);

	init_gpio_input(
			RAIN_PULSE_CRM_CLOCK,
			RAIN_PULSE_PORT,
			RAIN_PULSE_PIN,
			GPIO_PULL_UP);
}

void init_rain_exint(){
	printf("init rain exint\r\n");
	exint_init_type exint_init_struct;

	crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(RAIN_CRM_CLOCK, TRUE);

	gpio_exint_line_config(GPIO_PORT_SOURCE_GPIOA, GPIO_PINS_SOURCE8);

	exint_default_para_init(&exint_init_struct);
	exint_init_struct.line_enable = TRUE;
	exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
	exint_init_struct.line_select = EXINT_LINE_8;
	exint_init_struct.line_polarity = EXINT_TRIGGER_BOTH_EDGE;
	exint_init(&exint_init_struct);

	exint_interrupt_enable(EXINT_LINE_8, TRUE);

	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
	nvic_irq_enable(EXINT9_5_IRQn, 4, 0);

	// init PA11
	printf("init pulse exint\r\n");
//	crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(RAIN_PULSE_CRM_CLOCK, TRUE);

	gpio_exint_line_config(GPIO_PORT_SOURCE_GPIOA, GPIO_PINS_SOURCE11);

	exint_default_para_init(&exint_init_struct);
	exint_init_struct.line_enable = TRUE;
	exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
	exint_init_struct.line_select = EXINT_LINE_11;
	exint_init_struct.line_polarity = EXINT_TRIGGER_BOTH_EDGE;
	exint_init(&exint_init_struct);

	exint_interrupt_enable(EXINT_LINE_11, TRUE);

	nvic_irq_enable(EXINT15_10_IRQn, 4, 0);
}

void EXINT9_5_IRQHandler(void)
{
	if (exint_flag_get(EXINT_LINE_8) != RESET) {
		// debouncing
		// delay_ms(1);
		/* clear interrupt pending bit */
		exint_flag_clear(EXINT_LINE_8);

		// at32_led_toggle(LED4);

		// rain_count++;
		if(raindrop_state == RAIN_STATE_DUMMY){
			raindrop_state = RAIN_STATE_0;
		}

//		if(rain_mode == RAIN_MODE_NOTIFY){
//			// sprintf(temp_rain, "\r\nIORAINCNT:1,%d\r\n", rain_count);
//			send_to_at_queue_fromISR("rain", 4);
//
//		}

	}
}

void EXINT15_10_IRQHandler(void)
{
	if (exint_flag_get(EXINT_LINE_11) != RESET) {
		// debouncing
		// delay_ms(1);
		/* clear interrupt pending bit */
		exint_flag_clear(EXINT_LINE_11);

		// at32_led_toggle(LED4);

		if(pulse_state == RAIN_STATE_DUMMY){
			pulse_state = RAIN_STATE_0;
		}


	}
}

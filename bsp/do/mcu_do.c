/*
 * mcu_do.c
 *
 *  Created on: 2023 Feb 23
 *      Author: ruffman
 */
#include "at32f415_board.h"

static gpio_type* do_gpio_port[] = {
		DO_1_PORT,
		DO_2_PORT,
		DO_3_PORT,
		DO_4_PORT
};
static uint16_t do_gpio_pin[] = {
		DO_1_PIN,
		DO_2_PIN,
		DO_3_PIN,
		DO_4_PIN
};

void init_do_gpio(){
	init_gpio_output(
			DO_1_CRM_CLOCK,
			DO_1_PORT,
			DO_1_PIN,
			GPIO_PULL_DOWN
	);
	init_gpio_output(
			DO_2_CRM_CLOCK,
			DO_2_PORT,
			DO_2_PIN,
			GPIO_PULL_DOWN
	);
	init_gpio_output(
			DO_3_CRM_CLOCK,
			DO_3_PORT,
			DO_3_PIN,
			GPIO_PULL_DOWN
	);
	init_gpio_output(
			DO_4_CRM_CLOCK,
			DO_4_PORT,
			DO_4_PIN,
			GPIO_PULL_DOWN
	);
	gpio_off(DO_1_PORT,DO_1_PIN);
	gpio_off(DO_2_PORT,DO_2_PIN);
	gpio_off(DO_3_PORT,DO_3_PIN);
	gpio_off(DO_4_PORT,DO_4_PIN);
}

void do_ctrl(uint8_t channel, uint8_t onoff){
	if(onoff){
		gpio_on(do_gpio_port[channel - 1], do_gpio_pin[channel - 1]);
	}else{
		gpio_off(do_gpio_port[channel - 1], do_gpio_pin[channel - 1]);
	}
}

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
		DO_4_PORT,
		DO_5_PORT,
		DO_6_PORT,
		DO_7_PORT,
		DO_8_PORT
};
static uint16_t do_gpio_pin[] = {
		DO_1_PIN,
		DO_2_PIN,
		DO_3_PIN,
		DO_4_PIN,
		DO_5_PIN,
		DO_6_PIN,
		DO_7_PIN,
		DO_8_PIN
};
static uint16_t do_gpio_status[8] = {0};

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
	init_gpio_output(
			DO_5_CRM_CLOCK,
			DO_5_PORT,
			DO_5_PIN,
			GPIO_PULL_DOWN
	);
	init_gpio_output(
			DO_6_CRM_CLOCK,
			DO_6_PORT,
			DO_6_PIN,
			GPIO_PULL_DOWN
	);
	init_gpio_output(
			DO_7_CRM_CLOCK,
			DO_7_PORT,
			DO_7_PIN,
			GPIO_PULL_DOWN
	);
	init_gpio_output(
			DO_8_CRM_CLOCK,
			DO_8_PORT,
			DO_8_PIN,
			GPIO_PULL_DOWN
	);
	gpio_off(DO_1_PORT,DO_1_PIN);
	gpio_off(DO_2_PORT,DO_2_PIN);
	gpio_off(DO_3_PORT,DO_3_PIN);
	gpio_off(DO_4_PORT,DO_4_PIN);
	gpio_off(DO_5_PORT,DO_5_PIN);
	gpio_off(DO_6_PORT,DO_6_PIN);
	gpio_off(DO_7_PORT,DO_7_PIN);
	gpio_off(DO_8_PORT,DO_8_PIN);
}

static void do_ctrl_all(uint8_t onoff){
	for(int i = 0; i < 8; i++){
		if(onoff){
			gpio_on(do_gpio_port[i], do_gpio_pin[i]);
			do_gpio_status[i] = 1;
		}else{
			gpio_off(do_gpio_port[i], do_gpio_pin[i]);
			do_gpio_status[i] = 0;
		}
	}
}

void do_ctrl(uint8_t channel, uint8_t onoff){
	if(channel == 0){
		do_ctrl_all(onoff);
		return;
	}

	if(onoff){
		gpio_on(do_gpio_port[channel - 1], do_gpio_pin[channel - 1]);
		do_gpio_status[channel -1] = 1;
	}else{
		gpio_off(do_gpio_port[channel - 1], do_gpio_pin[channel - 1]);
		do_gpio_status[channel - 1] = 0;
	}
}
uint8_t do_ctrl_get_status(uint8_t channel){
	return do_gpio_status[channel - 1];
}

/*
 * mcu_relay.c
 *
 *  Created on: 2023 Feb 22
 *      Author: ruffman
 */
#include "at32f415_board.h"

static gpio_type* relay_gpio_port[] = {
		RELAY_1_PORT,
		RELAY_2_PORT,
		RELAY_3_PORT,
		RELAY_4_PORT
};
static uint16_t relay_gpio_pin[] = {
		RELAY_1_PIN,
		RELAY_2_PIN,
		RELAY_3_PIN,
		RELAY_4_PIN
};

uint16_t relay_gpio_status[4] = {0};

void init_relay_gpio(){
	init_gpio_output(
			RELAY_1_CRM_CLOCK,
			RELAY_1_PORT,
			RELAY_1_PIN,
			GPIO_PULL_DOWN
	);
	init_gpio_output(
			RELAY_2_CRM_CLOCK,
			RELAY_2_PORT,
			RELAY_2_PIN,
			GPIO_PULL_DOWN
	);
	init_gpio_output(
			RELAY_3_CRM_CLOCK,
			RELAY_3_PORT,
			RELAY_3_PIN,
			GPIO_PULL_DOWN
	);
	init_gpio_output(
			RELAY_4_CRM_CLOCK,
			RELAY_4_PORT,
			RELAY_4_PIN,
			GPIO_PULL_DOWN
	);
	gpio_off(RELAY_1_PORT,RELAY_1_PIN);
	gpio_off(RELAY_2_PORT,RELAY_2_PIN);
	gpio_off(RELAY_3_PORT,RELAY_3_PIN);
	gpio_off(RELAY_4_PORT,RELAY_4_PIN);
}
static void relay_ctrl_all(uint8_t onoff){
	for(int i = 0; i< 4; i++){
		if(onoff){
			gpio_on(relay_gpio_port[i],
					relay_gpio_pin[i]);
			relay_gpio_status[i] = 1;
		}else{
			gpio_off(relay_gpio_port[i],
					relay_gpio_pin[i]);
			relay_gpio_status[i] = 0;
		}
	}
}
void relay_ctrl(uint8_t channel, uint8_t onoff){
	if(channel == 0){
		relay_ctrl_all(onoff);
		return;
	}
	if(onoff){
		gpio_on(relay_gpio_port[channel - 1],
				relay_gpio_pin[channel - 1]);
		relay_gpio_status[channel - 1] = 1;
	}else{
		gpio_off(relay_gpio_port[channel - 1],
				relay_gpio_pin[channel - 1]);
		relay_gpio_status[channel - 1] = 0;
	}
}
uint8_t relay_ctrl_get_status(uint8_t channel){
	return relay_gpio_status[channel - 1];
}

/*
 * mcu_power.c
 *
 *  Created on: 2023 Feb 22
 *      Author: ruffman
 */
#include "at32f415_board.h"

static gpio_type* pwr_gpio_port[] = {
		RS232_1_POWER_PORT,
		RS485_1_POWER_PORT,
		RS232_2_POWER_PORT,
		RS485_2_POWER_PORT
};
static uint16_t pwr_gpio_pin[] = {
		RS232_1_POWER_PIN,
		RS485_1_POWER_PIN,
		RS232_2_POWER_PIN,
		RS485_2_POWER_PIN
};



void enable_RS232_1_pwr(){
	gpio_on(RS232_1_POWER_PORT,RS232_1_POWER_PIN);
}
void disable_RS232_1_pwr(){
	gpio_off(RS232_1_POWER_PORT,RS232_1_POWER_PIN);
}
void enable_RS485_1_pwr(){
	gpio_on(RS485_1_POWER_PORT,RS485_1_POWER_PIN);
}
void disable_RS485_1_pwr(){
	gpio_off(RS485_1_POWER_PORT,RS485_1_POWER_PIN);
}
void enable_RS232_2_pwr(){
	gpio_on(RS232_2_POWER_PORT,RS232_2_POWER_PIN);
}
void disable_RS232_2_pwr(){
	gpio_off(RS232_2_POWER_PORT,RS232_2_POWER_PIN);
}
void enable_RS485_2_pwr(){
	gpio_on(RS485_2_POWER_PORT,RS485_2_POWER_PIN);
}
void disable_RS485_2_pwr(){
	gpio_off(RS485_2_POWER_PORT,RS485_2_POWER_PIN);
}

void RS232_RS485_pwr_ctrl(
		uint8_t channel,
		uint8_t onoff){
	if(onoff){
		gpio_on(pwr_gpio_port[channel], pwr_gpio_pin[channel]);
	}else{
		gpio_off(pwr_gpio_port[channel], pwr_gpio_pin[channel]);
	}
}

void init_RS232_RS485_pwr_gpio(){
	init_gpio_output(
		RS232_1_POWER_CRM_CLOCK,
		RS232_1_POWER_PORT,
		RS232_1_POWER_PIN,
		GPIO_PULL_DOWN
	);
	init_gpio_output(
		RS232_2_POWER_CRM_CLOCK,
		RS232_2_POWER_PORT,
		RS232_2_POWER_PIN,
		GPIO_PULL_DOWN
	);
	init_gpio_output(
		RS485_2_POWER_CRM_CLOCK,
		RS485_2_POWER_PORT,
		RS485_2_POWER_PIN,
		GPIO_PULL_DOWN
	);
	disable_RS232_1_pwr();
	disable_RS485_1_pwr();
	disable_RS232_2_pwr();
	disable_RS485_2_pwr();
}




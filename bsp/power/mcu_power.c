/*
 * mcu_power.c
 *
 *  Created on: 2023 Feb 22
 *      Author: ruffman
 */
#include "at32f415_board.h"

static gpio_type* pwr_gpio_port[] = {
		ADC_POWER_PORT,
		SDI_1_POWER_PORT,
		RS485_1_POWER_PORT,
		RS232_1_POWER_PORT,
		VCCOUT_1_POWER_PORT
};
static uint16_t pwr_gpio_pin[] = {
		ADC_POWER_PIN,
		SDI_1_POWER_PIN,
		RS485_1_POWER_PIN,
		RS232_1_POWER_PIN,
		VCCOUT_1_POWER_PIN
};

static crm_periph_clock_type pwr_gpio_crm[] = {
		ADC_POWER_CRM_CLOCK,
		SDI_1_POWER_CRM_CLOCK,
		RS485_1_POWER_CRM_CLOCK,
		RS232_1_POWER_CRM_CLOCK,
		VCCOUT_1_POWER_CRM_CLOCK
};

uint8_t vo_gpio_status[5] = {0};

/*

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
*/
static void RS232_RS485_pwr_ctrl_all(uint8_t onoff){
	for(int i=0; i< 5; i++){
		if(onoff){
			gpio_on(pwr_gpio_port[i], pwr_gpio_pin[i]);
			vo_gpio_status[i] = 1;
		}else{
			gpio_off(pwr_gpio_port[i], pwr_gpio_pin[i]);
			vo_gpio_status[i] = 0;
		}
	}
}
void RS232_RS485_pwr_ctrl(
		uint8_t channel,
		uint8_t onoff){
	if(channel == 0){

		RS232_RS485_pwr_ctrl_all(onoff);
		return;
	}
	if(onoff){
		gpio_on(pwr_gpio_port[channel-1], pwr_gpio_pin[channel-1]);
		vo_gpio_status[channel-1] = 1;
	}else{
		gpio_off(pwr_gpio_port[channel-1], pwr_gpio_pin[channel-1]);
		vo_gpio_status[channel-1] = 0;
	}
}
uint8_t RS232_RS485_get_gpio_status(uint8_t channel){
	return vo_gpio_status[channel - 1];
}

void init_RS232_RS485_pwr_gpio(){
//	init_gpio_output(
//		RS232_1_POWER_CRM_CLOCK,
//		RS232_1_POWER_PORT,
//		RS232_1_POWER_PIN,
//		GPIO_PULL_DOWN
//	);
//	init_gpio_output(
//		RS232_2_POWER_CRM_CLOCK,
//		RS232_2_POWER_PORT,
//		RS232_2_POWER_PIN,
//		GPIO_PULL_DOWN
//	);
//	init_gpio_output(
//		RS485_2_POWER_CRM_CLOCK,
//		RS485_2_POWER_PORT,
//		RS485_2_POWER_PIN,
//		GPIO_PULL_DOWN
//	);
//	disable_RS232_1_pwr();
//	disable_RS485_1_pwr();
//	disable_RS232_2_pwr();
//	disable_RS485_2_pwr();
	for(int i = 0; i< 5; i++){
		init_gpio_output(
			pwr_gpio_crm[i],
			pwr_gpio_port[i],
			pwr_gpio_pin[i],
			GPIO_PULL_DOWN
		);
	}
	for(int i=0; i< 5; i++){
		gpio_off(pwr_gpio_port[i], pwr_gpio_pin[i]);
	}
}




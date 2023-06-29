/*
 * adc_power.c
 *
 *  Created on: 2023 Feb 22
 *      Author: ruffman
 */

#include "at32f415_board.h"


void init_adc_power_gpio(){
//	init_gpio_output(
//	ADC_POWER_CRM_CLOCK,
//	ADC_POWER_PORT,
//	ADC_POWER_PIN,
//	GPIO_PULL_DOWN
//	);
//	gpio_off(ADC_POWER_PORT,
//			ADC_POWER_PIN);
}


void adc_power_ctrl(uint8_t onoff){
//	if(onoff){
//		enable_adc_power();
//	}else{
//		disable_adc_power();
//	}
	RS232_RS485_pwr_ctrl(PWR_CTRL_ADC, onoff);
}



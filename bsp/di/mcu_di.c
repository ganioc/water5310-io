/*
 * mcu_di.c
 *
 *  Created on: 2023 Feb 23
 *      Author: ruffman
 */

#include "at32f415_board.h"

//enum DI_MODE di_channel_mode[] = { STATUS_QUERY };

struct DI_CHAN di_chan[] = {
		{
			id: 0,
			mode: STATUS_QUERY,
			count: 0,
			value: 0
		},
		{
			id: 1,
			mode: STATUS_QUERY,
			count: 0,
			value: 0
		},
		{
			id: 2,
			mode: STATUS_QUERY,
			count: 0,
			value: 0
		},
		{
			id: 3,
			mode: STATUS_QUERY,
			count: 0,
			value: 0
		},
		{
			id: 4,
			mode: STATUS_QUERY,
			count: 0,
			value: 0
		},
		{
			id: 5,
			mode: STATUS_QUERY,
			count: 0,
			value: 0
		},
		{
			id: 6,
			mode: STATUS_QUERY,
			count: 0,
			value: 0
		},
		{
			id: 7,
			mode: STATUS_QUERY,
			count: 0,
			value: 0
		}
};

void init_di_gpio(){
	init_gpio_input(
			DI_1_CRM_CLOCK,
			DI_1_PORT,
			DI_1_PIN,
			GPIO_PULL_UP);
	init_gpio_input(
			DI_2_CRM_CLOCK,
			DI_2_PORT,
			DI_2_PIN,
			GPIO_PULL_UP);
	init_gpio_input(
			DI_3_CRM_CLOCK,
			DI_3_PORT,
			DI_3_PIN,
			GPIO_PULL_UP);
	init_gpio_input(
			DI_4_CRM_CLOCK,
			DI_4_PORT,
			DI_4_PIN,
			GPIO_PULL_UP);
	init_gpio_input(
			DI_5_CRM_CLOCK,
			DI_5_PORT,
			DI_5_PIN,
			GPIO_PULL_UP);
	init_gpio_input(
			DI_6_CRM_CLOCK,
			DI_6_PORT,
			DI_6_PIN,
			GPIO_PULL_UP);
	init_gpio_input(
			DI_7_CRM_CLOCK,
			DI_7_PORT,
			DI_7_PIN,
			GPIO_PULL_UP);
	init_gpio_input(
			DI_8_CRM_CLOCK,
			DI_8_PORT,
			DI_8_PIN,
			GPIO_PULL_UP);

}

uint8_t di_mode_get(uint8_t channel){
	return (uint8_t)di_chan[channel - 1].mode;
}
void di_mode_set(uint8_t channel, uint8_t mode){
	switch(mode){
	case 0:
		di_chan[channel - 1].mode = STATUS_QUERY;
		break;
	case 1:
		di_chan[channel - 1].mode = STATUS_CHANGE_NOTIFY;
		break;
	case 2:
		di_chan[channel - 1].mode = COUNTING_QUERY;
		break;
	case 3:
		di_chan[channel - 1].mode = COUNTING_CHANGE_NOTIFY;
		break;
	default :
		printf("wrong mode!\r\n");
		break;
	}
}
void di_count_set(uint8_t channel, uint16_t count){
	di_chan[channel - 1].count = count;
}
void di_count_get(uint8_t channel, uint8_t* mode, uint16_t* count){
	uint8_t state = 0;
	*mode = (uint8_t)di_chan[channel - 1].mode;

	switch(channel){
	case 1:
		state = gpio_read(DI_1_PORT, DI_1_PIN);
		break;
	case 2:
		state = gpio_read(DI_2_PORT, DI_2_PIN);
		break;
	case 3:
		state = gpio_read(DI_3_PORT, DI_3_PIN);
		break;
	case 4:
		state = gpio_read(DI_4_PORT, DI_4_PIN);
		break;
	case 5:
		state = gpio_read(DI_5_PORT, DI_5_PIN);
		break;
	case 6:
		state = gpio_read(DI_6_PORT, DI_6_PIN);
		break;
	case 7:
		state = gpio_read(DI_7_PORT, DI_7_PIN);
		break;
	case 8:
		state = gpio_read(DI_8_PORT, DI_8_PIN);
		break;
	default:
		printf("wrong channel\r\n");
		break;
	}

	di_chan[channel - 1].value = state;
	*count = state;
}


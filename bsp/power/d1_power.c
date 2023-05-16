/*
 * d1_power.c
 *
 *  Created on: 2023 Feb 28
 *      Author: ruffman
 */


#include "at32f415_board.h"

void init_d1_power_gpio(){
	init_gpio_output(
			D1_POWER_GPIO_CLK,
			D1_POWER_GPIO_PORT,
			D1_POWER_PIN,
			GPIO_PULL_DOWN
	);

	gpio_on(D1_POWER_GPIO_PORT,D1_POWER_PIN);
}

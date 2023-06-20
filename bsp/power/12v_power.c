/*
 * 12v_power.c
 *
 *  Created on: 2023 Jun 19
 *      Author: ruff
 */

#include "at32f415_board.h"


void init_pd1_12v_power_gpio(){

    // remap PD0/PD1,
    gpio_pin_remap_config(PD01_MUX,TRUE);

	init_gpio_output(
			PD1_12V_POWER_GPIO_CLK,
			PD1_12V_POWER_GPIO_PORT,
			PD1_12V_POWER_PIN,
			GPIO_PULL_DOWN
	);

	gpio_on(PD1_12V_POWER_GPIO_PORT,PD1_12V_POWER_PIN);
}

/*
 * 5v_power.c
 *
 *  Created on: 2023 Jun 20
 *      Author: ruff
 */

#include "at32f415_board.h"


void init_pd0_5v_power_gpio(){

    // remap PD0/PD1,
    gpio_pin_remap_config(PD01_MUX,TRUE);

	init_gpio_output(
			PD0_5V_POWER_GPIO_CLK,
			PD0_5V_POWER_GPIO_PORT,
			PD0_5V_POWER_PIN,
			GPIO_PULL_DOWN
	);

	gpio_on(PD0_5V_POWER_GPIO_PORT,PD0_5V_POWER_PIN);
}


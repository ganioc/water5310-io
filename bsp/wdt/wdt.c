/*
 * wdt.c
 *
 *  Created on: 2023 Mar 3
 *      Author: ruffman
 */

#include "at32f415_board.h"

void init_wdt() {
	if (crm_flag_get(CRM_WDT_RESET_FLAG) != RESET) {
		/* reset from wdt */
		crm_flag_clear(CRM_WDT_RESET_FLAG);

		printf("reset by wdt!\r\n");
	}

	/* disable register write protection */
	wdt_register_write_enable(TRUE);

	/* set the wdt divider value */
	wdt_divider_set(WDT_CLK_DIV_256);
	/* set reload value

	 timeout = reload_value * (divider / lick_freq )    (s)

	 lick_freq    = 40000 Hz
	 divider      = 4
	 reload_value = 3000

	 timeout = 3000 * (4 / 40000 ) = 0.3s = 300ms
	 */
	// 26s
	wdt_reload_value_set(0xFFF);

	/* reload wdt counter */
	wdt_counter_reload();

	/* enable wdt */
	wdt_enable();
}
// reload in freertos idle task
void wdt_reload(){
	wdt_counter_reload();
}

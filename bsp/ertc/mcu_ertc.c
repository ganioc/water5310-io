/*
 * ertc.c
 *
 *  Created on: 2023 Feb 21
 *      Author: ruffman
 */

#include "at32f415_board.h"

ertc_dt_type bpr_addr_tab[ERTC_BPR_DT_NUMBER] = { ERTC_DT1, ERTC_DT2, ERTC_DT3,
		ERTC_DT4, ERTC_DT5 };

flag_status get_bpr_flag() {
	if (ertc_bpr_data_read(ERTC_DT1) == ERTC_MAGIC) {
		return TRUE;
	}
	return FALSE;
}
void set_bpr_flag() {
	ertc_bpr_data_write(ERTC_DT1, ERTC_MAGIC);
}

void rtc_clock_init() {

	/* enable pwc periph clock */
	crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);

	/* enable battery powered domain access */
	pwc_battery_powered_domain_access(TRUE);

	if (get_bpr_flag() == FALSE) {

		printf("bpr reset\r\n");

		/* reset ertc bpr domain */
		crm_battery_powered_domain_reset(TRUE);
		crm_battery_powered_domain_reset(FALSE);

		/* enable the lext osc */
		crm_clock_source_enable(CRM_CLOCK_SOURCE_LEXT, TRUE);

		/* wait till lext is ready */
		while (crm_flag_get(CRM_LEXT_STABLE_FLAG) == RESET)
			;

		/* select the ertc clock source */
		crm_ertc_clock_select(CRM_ERTC_CLOCK_LEXT);

		/* enable the ertc clock */
		crm_ertc_clock_enable(TRUE);

		/* deinitializes the ertc registers */
		ertc_reset();

		/* wait for ertc apb registers synchronisation */
		ertc_wait_update();

		/* configure the ertc data register and ertc prescaler
		 ck_spre(1hz) = ertcclk(lext) /(ertc_clk_div_a + 1)*(ertc_clk_div_b + 1)*/
		ertc_divider_set(127, 255);

		/* configure the hour format is 24-hour format*/
		ertc_hour_mode_set(ERTC_HOUR_MODE_24);

		/* set the date: friday june 11th 2021 */
		ertc_date_set(23, 2, 9, 4);

		/* set the time to 06h 20mn 00s am */
		ertc_time_set(12, 0, 0, ERTC_AM);

		set_bpr_flag();

	} else {
		printf("bpr no need reset\r\n");
		/* wait for ertc registers update */
		ertc_wait_update();
	}
}


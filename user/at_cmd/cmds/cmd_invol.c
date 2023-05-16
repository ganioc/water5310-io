/*
 * cmd_invol.c
 *
 *  Created on: 2023 Mar 1
 *      Author: ruffman
 */

#include "cmds.h"
#include <stdlib.h>

void cmd_invol_read() {
	uint16_t vref, val;
	uint8_t channel, mode;

	char temp[20];

	print_log("read adc invol");

	adc_get(9, &vref, &val);
	sprintf(temp, "%d:%d", vref, val);
	print_log(temp);

	sprintf(temp, "+INVOL:%0.3f",
			((float)1.2 *10.1 * 4095 * val)/(vref*4096)
					);
	send_response_str(temp);

	send_response_ok();
}

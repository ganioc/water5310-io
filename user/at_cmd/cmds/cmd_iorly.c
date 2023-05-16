/*
 * cmd_iorly.c
 *
 *  Created on: 2023 Feb 21
 *      Author: ruffman
 */
#include "cmds.h"
#include <stdlib.h>

void cmd_iorly_write(char* str, int len){
	char temp[3];
	uint8_t relay_channel;
	uint8_t onoff = 0;

	temp[0] = str[0];
	temp[1] = 0;
	relay_channel = atoi(temp);

	temp[0] = str[2];
	temp[1] = 0;
	onoff = atoi(temp);

	print_log(str);
	if( relay_channel > 4 ||
			relay_channel < 1 ||
			onoff > 1 ||
			onoff < 0){
		send_response_error(AT_ERROR_PARAMETER);
	}else{
		relay_ctrl(relay_channel, onoff);
		send_response_ok();
	}
}


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
			relay_channel < 0 ||
			onoff > 1 ||
			onoff < 0){
		send_response_error(AT_ERROR_PARAMETER);
	}else{
		relay_ctrl(relay_channel, onoff);
		send_response_ok();
	}
}
void cmd_iorly_read(){
	uint16_t vref, val;
	uint8_t channel, mode;

	char temp[20];

	print_log("read iorly");

	sprintf(temp, "+IORLY:%d,%d",
					1,
					relay_ctrl_get_status(1)
					);
	send_response_str(temp);

	for(int i = 2; i <= 4; i++){
		sprintf(temp, "+IORLY:%d,%d\r\n",
				i,
				relay_ctrl_get_status(i)
				);
		send_response_str_raw(temp);
	}

	send_response_ok();
}


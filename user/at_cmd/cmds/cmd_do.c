/*
 * cmd_do.c
 *
 *  Created on: 2023 Feb 22
 *      Author: ruffman
 */
#include "cmds.h"
#include <stdlib.h>

void cmd_iodo_read(){
	print_log("read do mode");
	char temp [20];

	sprintf(temp, "+IODO:%d,%d",
					1,
					do_ctrl_get_status(1)
					);
	send_response_str(temp);

	for(int i = 2; i <= 8; i++){
		sprintf(temp, "+IODO:%d,%d\r\n",
				i,
				do_ctrl_get_status(i)
				);
		send_response_str_raw(temp);
	}

	send_response_ok();
}

void  cmd_iodo_write(char* str, int len){
	char temp[3];
	uint8_t channel, onoff;

	print_log(str);

	temp[0] =  str[0];
	temp[1] = 0;
	channel = atoi(temp);

	temp[0] = str[2];
	temp[1] = 0;
	onoff = atoi(temp);

	if(channel < 0 || channel > DO_CHANNEL_NUM){
		send_response_error(AT_ERROR_PARAMETER);
	}else{
		do_ctrl(channel, onoff);
		send_response_ok();
	}


}

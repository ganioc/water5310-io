/*
 * cmd_do.c
 *
 *  Created on: 2023 Feb 22
 *      Author: ruffman
 */
#include "cmds.h"
#include <stdlib.h>


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

	if(channel < 1 || channel > DO_CHANNEL_NUM){
		send_response_error(AT_ERROR_PARAMETER);
	}else{
		do_ctrl(channel, onoff);
		send_response_ok();
	}


}

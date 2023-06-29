/*
 * cmd_iovo.c
 *
 *  Created on: 2023 Feb 21
 *      Author: ruffman
 */

#include "cmds.h"
#include <string.h>
#include <stdlib.h>

void cmd_iovo_read(){
	print_log("read vo mode");
	char temp [20];

	sprintf(temp, "+IODIMODE:%d,%d",
					1,
					di_mode_get(1)
					);
	send_response_str(temp);

	for(int i = 2; i <= 8; i++){
		sprintf(temp, "+IODIMODE:%d,%d\r\n",
				i,
				di_mode_get(i)
				);
		send_response_str_raw(temp);
	}

	send_response_ok();
}

// AT+IOVO
void cmd_iovo_write(char* str, int len){
	char temp[3];
	uint8_t power_channel;
	uint8_t onoff = 0;

	temp[0] = str[0];
	temp[1] = 0;
	power_channel = atoi(temp);

	temp[0] = str[2];
	temp[1] = 0;
	onoff = atoi(temp);

	print_log(str);

	if( power_channel > 5 ||
			power_channel < 0 ||
			onoff > 1 ||
			onoff < 0){
		send_response_error(AT_ERROR_PARAMETER);
	}else{
		RS232_RS485_pwr_ctrl(power_channel, onoff);
		send_response_ok();
	}
}



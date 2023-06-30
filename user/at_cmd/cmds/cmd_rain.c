/*
 * cmd_rain.c
 *
 *  Created on: 2023 Feb 22
 *      Author: ruffman
 */
#include "cmds.h"
#include "stdlib.h"

void cmd_iorainmode_read(){
	char temp[32];
	print_log("read rain mode");

	sprintf(temp,"+IORAINMODE:%d,%d",
				1,
				get_rain_mode(1));

	send_response_str(temp);

	send_response_ok();
}
void cmd_iorainmode_write(char*str , int len){
	char temp[32];
	uint8_t channel, mode;

	temp[0] = str[0];
	temp[1] = 0;
	channel = atoi(temp);

	temp[0] = str[2];
	temp[1] = 0;
	mode = atoi(temp);

	print_log(str);

	if(mode < 0 || mode > 2){
		send_response_error(AT_ERROR_PARAMETER);
	}else{
		set_rain_mode(channel, mode);

		send_response_ok();
	}
}
void cmd_ioraincnt_write(char*str , int len){
	char temp[32];
	uint8_t channel;
	uint32_t count;
	int i;

	temp[0] = str[0];
	temp[1] = 0;
	channel = atoi(temp);

	for(i = 2; i< len; i++){
		temp[i-2] = str[i];
	}
	temp[i] = 0;
	count = atoi(temp);

	print_log(str);

	if(count < 0 ){
		send_response_error(AT_ERROR_PARAMETER);
	}else{
		set_rain_count(channel, count);

		send_response_ok();
	}
}
void cmd_iorainread_write(char*str , int len){
	char temp[32];
	print_log("read rain cnt");

	sprintf(temp,"+IORAINREAD:%d,%d",
				1,
				get_rain_count(1));

	send_response_str(temp);

	send_response_ok();
}

/*
 * cmd_di.c
 *
 *  Created on: 2023 Feb 22
 *      Author: ruffman
 */
#include "cmds.h"
#include <stdlib.h>

void cmd_iodimode_read(){
	print_log("read di mode");
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
void cmd_iodimode_write(char* str, int len){
	char temp[3];
	uint8_t channel, mode;
	print_log(str);

	temp[0] = str[0];
	temp[1] = 0;
	channel = atoi(temp);

	temp[0] = str[2];
	temp[1] = 0;
	mode = atoi(temp);

	if (channel < 1 || channel > 8 || mode < 0 || mode > 3) {
		send_response_error(AT_ERROR_PARAMETER);
	}else{
		di_mode_set(channel, mode);
		send_response_ok();
	}
}
void cmd_iodicnt_write(char* str, int len){
	char temp[32];
	uint8_t channel;
	uint16_t count;
	int i = 0;

	print_log(str);

	temp[0] =  str[0];
	temp[1] = 0;
	channel = atoi(temp);

	for(i = 2; i < len; i++){
		temp[i-2] = str[i];
	}
	temp[i] = 0;
	count = atoi(temp);

	sprintf(temp, "%d,%d", channel, count);
	print_log(temp);

	if(channel < 1 || channel > 8){
		send_response_error(AT_ERROR_PARAMETER);
	}else{
		di_count_set(channel, count);
		send_response_ok();
	}
}
void cmd_iodiread_write(char* str, int len){
	char temp[32];
	uint8_t channel;
	uint8_t mode;
	uint16_t count;

	temp[0] = str[0];
	temp[1] = 0;
	channel = atoi(temp);


	print_log(str);

	if(channel < 0 || channel > 8){
		send_response_error(AT_ERROR_PARAMETER);
	}
	else if(channel == 0){
		di_count_get(1, &mode, &count );
		sprintf(temp, "+IODIREAD:%d,%d,%d",1,mode, count);
		send_response_str(temp);

		for(int i = 2; i<= 8; i++){
			di_count_get(i, &mode, &count );
			sprintf(temp, "+IODIREAD:%d,%d,%d\r\n",i,mode, count);
			send_response_str_raw(temp);
		}
		send_response_ok();

	}else{
		di_count_get(channel, &mode, &count );
		sprintf(temp, "+IODIREAD:%d,%d,%d",channel,mode, count);

		send_response_str(temp);

		send_response_ok();
	}


}


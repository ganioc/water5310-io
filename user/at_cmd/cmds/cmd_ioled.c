/*
 * cmd_ioled.c
 *
 *  Created on: 2023 Jun 28
 *      Author: ruff
 */

#include "cmds.h"
#include <stdlib.h>

void cmd_ioledonoff_write(char* str, int len){
	char temp[3];
	uint8_t channel, onoff;

	print_log(str);

	temp[0] =  str[0];
	temp[1] = 0;
	channel = atoi(temp);

	temp[0] = str[2];
	temp[1] = 0;
	onoff = atoi(temp);

	if(channel != 1 || onoff > 1 || onoff < 0){
		send_response_error(AT_ERROR_PARAMETER);
	}else{
		at32_led_set_onoff_state(LED4, onoff);
		send_response_ok();
	}
}
void cmd_ioledonoff_read(){
	char temp[16];
	print_log("read onoff mode");

	sprintf(temp, "%d",at32_led_get_onoff(LED4));
	print_log(temp);

	send_response_ok();
}
void cmd_ioledblink_write(char* str, int len){
	char temp[16];
	uint8_t channel,index, temp_index;
	uint16_t onTime,offTime, repeatCnt;

	print_log(str);

	temp[0] = str[0];
	temp[1] = 0;
	channel = atoi(temp);

	index = 2;
	temp_index = 0;
	while(str[index] != ',' && index < len){
		temp[temp_index++] = str[index++];
	}
	temp[temp_index] = 0;
	onTime = atoi(temp);

	index++;
	temp_index =0;
	while(str[index] != ',' && index < len){
		temp[temp_index++] = str[index++];
	}
	temp[temp_index] = 0;
	offTime = atoi(temp);

	index++;
	temp_index=0;
	while(index < len){
		temp[temp_index++] = str[index++];
	}
	temp[temp_index] = 0;
	repeatCnt = atoi(temp);

	sprintf(temp, "on:%d", onTime);
	print_log(temp);
	sprintf(temp, "off:%d", offTime);
	print_log(temp);
	sprintf(temp, "repeat:%d", repeatCnt);
	print_log(temp);

	if( channel != 1 || onTime <= 0 || onTime >= 10000|| offTime <=0 || offTime >= 10000 || repeatCnt < 0){
		send_response_error(AT_ERROR_PARAMETER);
	}else{
		at32_led_set_blink_state(LED4, onTime,offTime, repeatCnt);
		send_response_ok();
	}

}
void cmd_ioledblink_read(){
	char temp[32];
	struct LED_STAUTS status;
	print_log("read blink mode");

	status = at32_led_get_status(LED4);

	sprintf(temp, "%d,%d,%d",status.onTime, status.offTime, status.repeatCnt);
	print_log(temp);

	send_response_ok();
}

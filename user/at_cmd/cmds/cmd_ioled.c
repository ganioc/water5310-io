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

}
void cmd_ioledblink_read(){

}

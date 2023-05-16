/*
 * cmd_btn.c
 *
 *  Created on: 2023 Feb 22
 *      Author: ruffman
 */

#include "cmds.h"

#include "ctype.h"

void cmd_iobtnsub_read(){
	char temp[32];

	print_log("read iobtnsub");

	if(user_button_get_click_sub() == 1){
		send_response_str("+IOBTNSUB:1,\"click\"");
	}
	if(user_button_get_long_sub() == 1){
		send_response_str("+IOBTNSUB:1,\"long\"");
	}
	send_response_ok();
}
void cmd_iobtnsub_write(char*str , int len){
	char temp[32];
	print_log(str);

	temp[0] = toupper(str[2]);

	if(temp[0] != 'L'){
		send_response_error(AT_ERROR_PARAMETER);
	}else{
		user_button_enable_long_click();
		send_response_ok();
	}
}
void cmd_iobtnunsub_write(char*str , int len){
	char temp[32];
	print_log(str);

	temp[0] = toupper(str[2]);

	if(temp[0] != 'L'){
		send_response_error(AT_ERROR_PARAMETER);
	}else{
		user_button_disable_long_click();
		send_response_ok();
	}
}

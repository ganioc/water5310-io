/*
 * at_parse.c
 *
 *  Created on: 2023 Feb 20
 *      Author: ruffman
 */
//#include "timers.h"
#include "FreeRTOS.h"
#include "task.h"

#include "at_parse.h"
#include "task_conf.h"

#include "cmds.h"

#include <string.h>
#include <ctype.h>

enum PARSE_STATE state = S_DUMMY;

uint8_t name_index;
uint8_t args_index;

uint8_t AT_in_handling = 0;


void reset_parse_state(){
	name_index = 0;
	args_index = 0;
	state = S_DUMMY;
}
void parserTimerCallback( TimerHandle_t xTimer ){
	// at32_led_toggle(LED3);
	print_log("+");
	send_response_timeout();
	reset_parse_state();
}



void enter_handling(){
	start_timer();
}
void exit_handling(char* code){
	reset_parse_state();
	stop_timer();
	send_response_error(code);
}

void end_handling(struct AT_CMD *cmd){
	stop_timer();
	handle_at_cmd(*cmd);
	reset_parse_state();
}

// AT+CDATE="2022-02-21T16:31:01.001"
// AT+CDATE="2022-02-22T10:53:55.001"
// AT+CDATE?
void parse_at_cmd(char* str, uint16_t* head, uint16_t* tail){
	struct AT_CMD cmd;
	cmd.type = _AT_UNKNOWN;

	while(*head != *tail){
		uint8_t ch = str[*tail];
		switch(state){
		case S_DUMMY:
			if(ch == 'A' || ch == 'a'){
				state = S_HEAD;
				name_index = 0;
				args_index = 0;
			}
			break;
		case S_HEAD:
			if(ch == 'T' || ch == 't'){
				state = S_PLUS;
				enter_handling();
			}else{
				print_log("parse head fail");
				state = S_DUMMY;
			}
			break;
		case S_PLUS:
			if(ch == '+'){
				state = S_TAG;
			}else if(ch == '\r'){
				cmd.type =_AT_EXEC;
				sprintf(cmd.name, "");
				end_handling(&cmd);
				break;
			}else{
				exit_handling(AT_ERROR_POSITION);

			}
			break;
		case S_TAG:
			if(ch == '?'&& name_index >0){
				cmd.name[name_index]=0;
				cmd.type = _AT_GET;
				state = S_CARRIAGE;
			}else if(ch == '='&& name_index >0){
				cmd.name[name_index]=0;
				state = S_OPERATOR;
			}
			else if(ch == '\r' && name_index >0){
				cmd.name[name_index]=0;
				cmd.type = _AT_EXEC;
				end_handling(&cmd);
				break;
			}else if(isalpha(ch) != 0 ){
				cmd.name[name_index++] = toupper(ch);
			}
			else{
				exit_handling(AT_ERROR_POSITION);
			}
			break;
		case S_OPERATOR:
			if(ch == '?' && args_index == 0){
				cmd.type = _AT_TEST;
				state = S_CARRIAGE;
			}else if(ch == '\r' && args_index > 0){
				cmd.args[args_index] = 0;
				end_handling(&cmd);
				break;
			}else if (isalpha(ch) != 0 ||
					isupper(ch) != 0||
					isdigit(ch) != 0||
					ch == '"' ||
					ch == '-' ||
					ch == '.' ||
					ch == ':' ||
					ch == ','){
				cmd.type = _AT_SET;
				cmd.args[args_index++] = ch;
			}else{
				exit_handling(AT_ERROR_PARAMETER);
			}
			break;
		case S_CARRIAGE:
			if(ch == '\r'){
				end_handling(&cmd);
				break;
			}else{
				exit_handling(AT_ERROR_POSITION);
			}
			break;
		default:
			break;
		}

		(*tail)++;
		if((*tail) >= AT_RX_BUFFER_LEN){
			(*tail) = 0;
		}
	}

}

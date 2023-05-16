/*
 * cmd_version.c
 *
 *  Created on: 2023 Feb 21
 *      Author: ruffman
 */
#include <string.h>

#include "cmds.h"


extern char version[];
extern char model[];

void cmd_version_exec(void){
	char str[32];
	sprintf(str, "%s_V%s", model, version);

	send_response_str(str);
	send_response_ok();
}
void cmd_version_read(void){
	send_response_str(version);
	send_response_ok();
}
void cmd_version_test(void){
	send_response_str("test VERSION");
	send_response_ok();
}
void cmd_version_write(char*str, int len){
	print_log("received set cmd");
	print_log(str);
	send_response_ok();
}

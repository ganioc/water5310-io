/*
 * cmd_restore.c
 *
 *  Created on: 2023 Feb 21
 *      Author: ruffman
 */
#include "cmds.h"

void cmd_restore_exec(){
	print_log("restore default state");
	send_response_ok();

}

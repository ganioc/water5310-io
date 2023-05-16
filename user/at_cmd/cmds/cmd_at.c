/*
 * cmd_at.c
 *
 *  Created on: 2023 Feb 20
 *      Author: ruffman
 */

#include "cmds.h"

void cmd_at_exec(){
	print_log("[AT] received");
	send_response_ok();
}

/*
 * cmd_rst.c
 *
 *  Created on: 2023 Feb 21
 *      Author: ruffman
 */


#include "cmds.h"

void cmd_rst_exec(){
	send_response_ok();
	print_log("system reset");

	vTaskDelay(RST_DELAY);

	nvic_system_reset();
}


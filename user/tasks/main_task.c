/*
 * main_task.c
 *
 *  Created on: 2023 Feb 19
 *      Author: ruffman
 */

#include "task_conf.h"
#include <stdio.h>

TaskHandle_t main_handler;


/* main task function , main task logic is here*/
void main_task_function(void *pvParameters)
{
  while(1)
  {

    at32_led_toggle(LED4);
    print_log("main task");
    vTaskDelay(5000);
  }
}



void init_main_task() {
	/* create main task */
	if (xTaskCreate((TaskFunction_t) main_task_function,
			(const char*) "Main_task", (uint16_t) 256, (void*) NULL,
			(UBaseType_t) 2, (TaskHandle_t*) &main_handler) != pdPASS) {
		printf(
				"Main task could not be created as there was insufficient heap memory remaining.\r\n");
	} else {
		printf("Main task was created successfully.\r\n");
	}
}

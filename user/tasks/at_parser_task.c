/*
 * at_parser_task.c
 *
 *  Created on: 2023 Feb 19
 *      Author: ruffman
 */

#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "task_conf.h"
#include "semphr.h"
#include "timers.h"

#include "at_struct.h"
#include "at_parse.h"

TaskHandle_t at_parser_handler;
SemaphoreHandle_t xRxISRMutex = NULL;

TimerHandle_t parserTimer = NULL;

uint8_t  at_rx_buf[AT_RX_BUFFER_LEN];
uint16_t at_rx_buf_head = 0, at_rx_buf_tail = 0;


void update_at_rx_buf(uint8_t*str, int len){
	for(int i=0; i < len; i++){
		at_rx_buf[at_rx_buf_head++] = str[i];
		if(at_rx_buf_head >= AT_RX_BUFFER_LEN){
			at_rx_buf_head = 0;
		}
	}
}

void start_timer(){
	xTimerStart(parserTimer, portMAX_DELAY);
}
void stop_timer(){
	xTimerStop(parserTimer, portMAX_DELAY);
}

void parse_at(){
	parse_at_cmd(at_rx_buf, &at_rx_buf_head, &at_rx_buf_tail );
}
void parse_binary(){

}


void at_parser_task_func(void *pvParameters) {

	print_log("init parser at callback");
	init_at_callback();

	while (1) {
        /* This task will execute when the master task already holds the mutex.
         * Attempting to take the mutex will place this task in the Blocked
         * state. */
        if( xSemaphoreTake( xRxISRMutex, portMAX_DELAY ) != pdPASS )
        {
            print_log("xRxISRMutext bad return");
        }else{
        	print_log("received AT cmd");
        	// at32_led_toggle(LED4);
        	parse_at();
        }
	}
}
void init_at_parser_task() {
	if (xTaskCreate((TaskFunction_t) at_parser_task_func,
			(const char*) "at_parser", (uint16_t) 512, (void*) NULL,
			(UBaseType_t) 2, (TaskHandle_t*) &at_parser_handler) != pdPASS) {
		printf(
				"at_parser task could not be created as there was insufficient heap memory remaining.\r\n");
	} else {
		printf("at_parser task was created successfully.\r\n");
	}
	xRxISRMutex = xSemaphoreCreateBinary();

	parserTimer = xTimerCreate( "ParserTimer", PARSER_TIMER_TICKS, pdFALSE, NULL, parserTimerCallback );

}

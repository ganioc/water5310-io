/*
 * print_log_task.c
 *
 *  Created on: 2023 Feb 19
 *      Author: ruffman
 */

#include "task_conf.h"
#include "string.h"

TaskHandle_t print_log_handler;
MessageBufferHandle_t msg_buf_handler;
static char buffer[MESSAGE_BUFFER_SIZE];

void print_log(char *str) {

	xMessageBufferSend(
	/* The message buffer to write to. */
	msg_buf_handler,
	/* The source of the data to send. */
	(void*) str,
	/* The length of the data to send. */
	strlen(str),
	/* The block time, should the buffer be full. */
	portMAX_DELAY);
}
void print_log_from_ISR(char *str) {
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	xMessageBufferSendFromISR(
	/* The message buffer to write to. */
	msg_buf_handler,
	/* The source of the data to send. */
	(void*) str,
	/* The length of the data to send. */
	strlen(str),
	/* The block time, should the buffer be full. */
	// portMAX_DELAY);
	&xHigherPriorityTaskWoken);
}

/* main task function , main task logic is here*/
void print_log_task_func(void *pvParameters) {
	int xReceivedBytes;
	while (1) {
		xReceivedBytes = xMessageBufferReceive( /* The message buffer to receive from. */
		msg_buf_handler,
		/* Location to store received data. */
		buffer,
		/* Maximum number of bytes to receive. */
		sizeof(buffer),
		/* Ticks to wait if buffer is empty. */
		portMAX_DELAY);
		printf(": %s\r\n", buffer);
		memset(buffer, 0,  MESSAGE_BUFFER_SIZE);
	}
}

void init_print_log_task() {
	if (xTaskCreate((TaskFunction_t) print_log_task_func,
			(const char*) "print_log", (uint16_t) 256, (void*) NULL,
			(UBaseType_t) 1, (TaskHandle_t*) &print_log_handler) != pdPASS) {
		printf(
				"print_log task could not be created as there was insufficient heap memory remaining.\r\n");
	} else {
		printf("print_log task was created successfully.\r\n");
	}

	msg_buf_handler = xMessageBufferCreate( MESSAGE_BUFFER_SIZE);
}

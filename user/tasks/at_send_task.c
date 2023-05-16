/*
 * at_send_task.c
 *
 *  Created on: 2023 Feb 21
 *      Author: ruffman
 */

#include "task_conf.h"
#include "semphr.h"

#include <string.h>

TaskHandle_t at_send_handler;
//SemaphoreHandle_t xSendISRMutex = NULL;
QueueHandle_t   at_send_queue;
SemaphoreHandle_t xTxISRMutex = NULL;


struct AT_Message message;

uint8_t   at_send_id = 0;

extern uint8_t at_tx_buf[];
extern uint16_t at_tx_buf_idx, at_tx_buf_amount;
extern char model[];
extern char version[];


// send to at port through queue to enable multi-sender working
void send_to_at_queue(uint8_t* str, int len){
	struct AT_Message tx_message;
	tx_message.id = at_send_id++;
	tx_message.len = len;
	memcpy(tx_message.data, str, len);
	xQueueSend(at_send_queue, &tx_message, portMAX_DELAY);
}
void send_to_at_queue_fromISR(uint8_t* str, int len){
	BaseType_t xHigherPriorityTaskWoken;
	struct AT_Message tx_message;
	tx_message.id = at_send_id++;
	tx_message.len = len;
	memcpy(tx_message.data, str, len);
	xQueueSendFromISR(at_send_queue, &tx_message, &xHigherPriorityTaskWoken);
}
void send_response_ok(){
//	send_tx_buf("\r\nOK\r\n",6);
	send_to_at_queue("\r\nOK\r\n",6);
}
void send_response_timeout(){
	// send_tx_buf("\r\nTIMEOUT\r\n",11);
	send_to_at_queue("\r\nTIMEOUT\r\n",11);
}
void send_response_error(char* code){
	char buf[48];
	sprintf(buf, "\r\nERROR:%s\r\n",code);
	// send_tx_buf(buf, strlen(buf));
	send_to_at_queue(buf, strlen(buf));
}
void send_response_ready(){
	// send_tx_buf("\r\nREADY\r\n",9);
	send_to_at_queue("\r\nREADY\r\n",9);
}
void send_response_str(char* str){
	char buf[48];
	sprintf(buf, "\r\n%s\r\n", str);
	// send_tx_buf(buf,strlen(buf));
	send_to_at_queue(buf,strlen(buf));
}
void send_response_str_raw(char* str){
	char buf[48];
	sprintf(buf, "%s", str);
	// send_tx_buf(buf,strlen(buf));
	send_to_at_queue(buf,strlen(buf));
}

void print_initial_info(){
	char buf[32];
	sprintf(buf,"VER: %s_V%s\r\n", model, version);
//	send_tx_buf(buf,strlen(buf));
//	send_response_ready();
	send_to_at_queue((uint8_t *)buf, strlen(buf));
}

void at_send_task_func(void *pvParameters) {

	// Enable 1st uart tx,
	xSemaphoreGive(xTxISRMutex);

	print_initial_info();
	send_response_ok();


	while (1) {
		if(xQueueReceive(at_send_queue, &message, portMAX_DELAY) != pdPASS){
			print_log("xQueueReceive at send queue bad");
		}else{
			printf("message id: %d\r\n", message.id);
			printf("message len: %d\r\n", message.len);

			if(xSemaphoreTake( xTxISRMutex, portMAX_DELAY ) != pdPASS){
				print_log("xTxISRMutex take failed");
			}

			// copy to tx buffer,
			memcpy(at_tx_buf, message.data, message.len);

			// enable tx interrupt
			at_tx_buf_amount = message.len;
			at_tx_buf_idx = 0;
			print_log("send tx buf");

			usart_interrupt_enable(D1_UART, USART_TDBE_INT, TRUE);
		}
	}
}
void init_at_send_task(){
	if (xTaskCreate((TaskFunction_t) at_send_task_func,
			(const char*) "at_send", (uint16_t) 256, (void*) NULL,
			(UBaseType_t) 2, (TaskHandle_t*) &at_send_handler) != pdPASS) {
		printf(
				"at_send task could not be created as there was insufficient heap memory remaining.\r\n");
	} else {
		printf("at_send task was created successfully.\r\n");
	}

	at_send_queue = xQueueCreate(AT_TX_QUEUE_LEN, AT_TX_QUEUE_ITEM_SIZE);

	if(at_send_queue == NULL){
		printf("at_send_queue created failed\r\n");
	}

	xTxISRMutex = xSemaphoreCreateBinary();

	if(xTxISRMutex ==  NULL){
		printf("xTxISRMutex created failed\r\n");
	}
}

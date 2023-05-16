/*
 * task_conf.h
 *
 *  Created on: 2023 Feb 19
 *      Author: ruffman
 */

#ifndef INCLUDE_TASK_CONF_H_
#define INCLUDE_TASK_CONF_H_


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "message_buffer.h"

#include "at32f415_board.h"


// print_log_task
#define MESSAGE_BUFFER_SIZE 64

void init_print_log_task();
void print_log(char *str);
void print_log_from_ISR(char *str);

/// main task
void init_main_task();

// at parser task
#define AT_RX_BUFFER_LEN  128

void init_at_parser_task();
void update_at_rx_buf(uint8_t*str, int len);
void send_tx_buf(uint8_t* str, int len);
void start_timer();
void stop_timer();

void send_response_ok();
void send_response_timeout();
void send_response_error(char* code);
void send_response_str(char* str);
void send_response_str_raw(char* str);

// at send task
#define AT_TX_BUFFER_LEN  64
#define AT_TX_QUEUE_LEN   5

void init_at_send_task();

struct AT_Message{
	char      id;
	uint8_t   len;
	char      data[AT_TX_BUFFER_LEN];
};

#define AT_TX_QUEUE_ITEM_SIZE   sizeof(struct AT_Message)

void send_to_at_queue(uint8_t* str, int len);
void send_to_at_queue_fromISR(uint8_t* str, int len);


#endif /* INCLUDE_TASK_CONF_H_ */

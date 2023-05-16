/*
 * at_parse.h
 *
 *  Created on: 2023 Feb 20
 *      Author: ruffman
 */

#ifndef USER_AT_CMD_AT_PARSE_H_
#define USER_AT_CMD_AT_PARSE_H_

#include "at_struct.h"
#include "timers.h"

#define PARSER_TIMER_TICKS 500

enum PARSE_STATE{
	S_DUMMY,
	S_HEAD,
	S_PLUS,
	S_TAG,
	S_OPERATOR,
	S_ARG,
	S_CARRIAGE
};

void parse_at_cmd(char* str, uint16_t* head, uint16_t* tail);

void parserTimerCallback( TimerHandle_t xTimer );


#endif /* USER_AT_CMD_AT_PARSE_H_ */

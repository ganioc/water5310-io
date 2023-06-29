/*
 * at_struct.c
 *
 *  Created on: 2023 Feb 20
 *      Author: ruffman
 */
#include <string.h>
#include <ctype.h>

#include "at_struct.h"
#include "task_conf.h"
#include "at_parse.h"
#include "cmds.h"

extern struct AT_CALLBACK at_cmd_list[];
extern int NUM_AT_CALLBACK;


uint32_t makeHash( char *pCmd )
{
    uint16_t ch;
    uint32_t hash;
    uint16_t i=0;

    ch = 0;
    hash = 0x05;

    while((ch = *pCmd++))
        hash += (ch << (i++));
    return hash;
}

void init_at_callback(){

	printf("size of lst:%d\r\n", NUM_AT_CALLBACK);
	printf("size of ele:%d\r\n", sizeof(at_cmd_list[0]));


	for(int i=0; i< NUM_AT_CALLBACK; i++){
		at_cmd_list[i].hash = makeHash(at_cmd_list[i].name);
	}

	// check duplicate names��
	for(int i =0; i< NUM_AT_CALLBACK; i++){
		for(int j=0; j<NUM_AT_CALLBACK; j++){
			if(i != j && at_cmd_list[i].hash == at_cmd_list[j].hash){
				printf("Hash is duplicate! exit!\r\n");
				print_log("Duplicate:");
				print_log(at_cmd_list[i].name);
			}
		}
	}
}

struct AT_CALLBACK* search_at_callback(uint32_t hash){
	struct AT_CALLBACK *lst = at_cmd_list;

	for(int i=0; i< NUM_AT_CALLBACK; i++){
		if(lst[i].hash == hash){
			return &lst[i];
		}
	}
	return NULL;
}
struct AT_CALLBACK* search_at_callback_by_name(char* name){
	uint32_t hash = makeHash(name);

	return search_at_callback(hash);
}

void handle_at_cmd(struct AT_CMD cmd){
	struct AT_CALLBACK * cb = search_at_callback_by_name(cmd.name);
	if(cb == NULL){
		send_response_error(AT_ERROR_POSITION);
		return;
	}
	switch (cmd.type) {
	case _AT_UNKNOWN:
		send_response_error(AT_ERROR_POSITION);
		break;
	case _AT_TEST:

		(cb->test_cb == NULL)?(send_response_error(AT_ERROR_UNKNOWN)):cb->test_cb();

		break;
	case _AT_SET:
		(cb->write_cb != NULL)?(cb->write_cb(cmd.args, strlen(cmd.args))):(send_response_error(AT_ERROR_UNKNOWN));
		break;
	case _AT_GET:
		(cb->read_cb != NULL)?(cb->read_cb()):(send_response_error(AT_ERROR_UNKNOWN));
		break;
	case _AT_URC:
		send_response_error(AT_ERROR_POSITION);
		break;
	case _AT_EXEC:
		(cb->exec_cb != NULL)?(cb->exec_cb()):(send_response_error(AT_ERROR_UNKNOWN));
		break;
	default:
		send_response_error(AT_ERROR_POSITION);
	}
}

/*
 * at_cdate.c
 *
 *  Created on: 2023 Feb 21
 *      Author: ruffman
 */

#include "cmds.h"
#include <string.h>
#include <stdlib.h>

void cmd_cdate_read(){
	char str[48];
	ertc_time_type time;
	ertc_calendar_get(&time);
	// 24 hours
	sprintf(str, "+CDATE:\"%04d-%02d-%02dT%02d:%02d:%02d.%03d\"",
			2000+ time.year,
			time.month,
			time.day,
			time.hour,
			time.min,
			time.sec,
			(255 - ertc_sub_second_get())*1000/256);

	send_response_str(str);

	send_response_ok();
}
void cmd_cdate_write(char* str, int len){
	uint32_t sbs;
	uint8_t year, month, day, hour, min, sec;
	char temp_str[4];

	print_log(str);

	temp_str[0] = str[3];
	temp_str[1] = str[4];
	temp_str[2] = 0;
	year =  atoi(temp_str);

	temp_str[0] = str[6];
	temp_str[1] = str[7];
	temp_str[2] = 0;
	month = atoi(temp_str);

	temp_str[0] = str[9];
	temp_str[1] = str[10];
	temp_str[2] = 0;
	day = atoi(temp_str);

	temp_str[0] = str[12];
	temp_str[1] = str[13];
	temp_str[2] = 0;
	hour = atoi(temp_str);

	temp_str[0] = str[15];
	temp_str[1] = str[16];
	temp_str[2] = 0;
	min = atoi(temp_str);

	temp_str[0] = str[18];
	temp_str[1] = str[19];
	temp_str[2] = 0;
	sec = atoi(temp_str);

	temp_str[0] = str[21];
	temp_str[1] = str[22];
	temp_str[2] = str[23];
	temp_str[3] = 0;
	sbs = atoi(temp_str);

	ertc_date_set(year,month,day,1);
	ertc_time_set(hour, min, sec, ERTC_24H);
//	ertc_sub_second_set(sbs*255/1000);

	send_response_ok();
}

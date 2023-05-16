/*
 * cmd_adc.c
 *
 *  Created on: 2023 Feb 22
 *      Author: ruffman
 */

#include "cmds.h"
#include <stdlib.h>

void cmd_ioadcpwr_write(char *str, int len) {
	char temp[2];
	uint8_t onoff;

	temp[0] = str[0];
	temp[1] = 0;

	onoff = atoi(temp);

	print_log(str);

	if (onoff < 0 || onoff > 1) {
		send_response_error(AT_ERROR_PARAMETER);
	} else {
		adc_power_ctrl(onoff);
		send_response_ok();
	}
}

void cmd_ioadcmode_write(char *str, int len) {
	char temp[3];
	uint8_t channel;
	uint8_t mode = 0;
	print_log(str);

	temp[0] = str[0];
	temp[1] = 0;
	channel = atoi(temp);

	temp[0] = str[2];
	temp[1] = 0;
	mode = atoi(temp);

	if (channel < 1 || channel > 8 || mode < 0 || mode > 1) {
		send_response_error(AT_ERROR_PARAMETER);
	}else{
		adc_mode_set(channel, mode);
		send_response_ok();
	}
}

void cmd_ioadcmode_read() {
	print_log("read adc mode");
	char temp[20];

	sprintf(temp, "+IOADCMODE:%d,%d",
					1,
					adc_mode_get(1)
					);
	send_response_str(temp);

	for(int i = 2; i <= 8; i++){
		sprintf(temp, "+IOADCMODE:%d,%d\r\n",
				i,
				adc_mode_get(i)
				);
		send_response_str_raw(temp);
	}
	send_response_ok();
}

void cmd_ioadcread_write(char *str, int len) {
	uint16_t vref, val;
	uint8_t channel, mode;
	char temp[32];

	print_log(str);

	temp[0] = str[0];
	temp[1] = 0;
	channel = atoi(temp);

	if(channel < 1 || channel > 8){
		send_response_error(AT_ERROR_PARAMETER);
	}else{
		mode = adc_mode_get(channel);
		adc_get(channel, &vref, &val);
		sprintf(temp, "%d:%d", vref, val);
		print_log(temp);

		sprintf(temp, "+IOADCREAD:%d,%d,%0.3f,%d",
				channel,
				mode,
				((float)1.2 * 4095 * val)/(vref*4096),
				val);

		send_response_str(temp);

		send_response_ok();
	}

}


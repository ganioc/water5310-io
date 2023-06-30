/*
 * cmd_adc.c
 *
 *  Created on: 2023 Feb 22
 *      Author: ruffman
 */

#include "cmds.h"
#include <stdlib.h>

extern uint16_t adc1_ordinary_value[ADC_MEASURE_NUM];

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
static float compute_val(uint8_t mode, uint16_t vref, uint16_t val){
	// ((float)1.2 * 4095 * val)/(vref*4096)
	float mVref = ((float) 1.2 * 4095) / vref;
	float v_coef = 2.0;
	float v_compu = (float)mVref * val / 4096;

	if(mode == 0){ // voltage
		return v_coef * v_compu;
	}else{ // current
		return v_compu*2.0/249.0;
	}

}
void cmd_ioadcread_write(char *str, int len) {
	uint16_t vref, val;
	uint8_t channel, mode;
	char temp[36];

	print_log(str);

	temp[0] = str[0];
	temp[1] = 0;
	channel = atoi(temp);

	if(channel < 0 || channel > 8){
		send_response_error(AT_ERROR_PARAMETER);
	}else if(channel == 0){

		adc_repeat_read();

		vref=adc1_ordinary_value[0];

		// get channel1
		mode = adc_mode_get(1);
		val = adc1_ordinary_value[1];
		// adc_get(1, &vref, &val);

		sprintf(temp, "+IOADCREAD:%d,%d,%0.3f,%d",
						1,
						mode,
						compute_val(mode, vref, val),
						val);

		send_response_str(temp);

		// get channel 2~8
		for(int i = 2; i <= 8 ; i++){
			mode = adc_mode_get(i);
			// adc_get(i, &vref, &val);
			val = adc1_ordinary_value[i];

			sprintf(temp, "+IOADCREAD:%d,%d,%0.3f,%d\r\n",
							i,
							mode,
							compute_val(mode, vref, val),
							val);

			send_response_str_raw(temp);

			// delay some time
			// vTaskDelay(10);
		}

		send_response_ok();

	}else{
		mode = adc_mode_get(channel);
		adc_get(channel, &vref, &val);
		sprintf(temp, "%d:%d", vref, val);
		print_log(temp);

		sprintf(temp, "+IOADCREAD:%d,%d,%0.3f,%d",
				channel,
				mode,
				compute_val(mode, vref, val),
				val);

		send_response_str(temp);

		send_response_ok();
	}

}


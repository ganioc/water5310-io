/*
 * sys_state.c
 *
 *  Created on: 2023 Feb 22
 *      Author: ruffman
 */

#include "sys_state.h"
#include "flash.h"
#include "iap.h"

extern struct ADC_CHAN chan_list[];
extern struct DI_CHAN di_chan[];

struct MCU_SYSTEM mcu = {
	state: BOOT,
	need_upgrade: NEEDLESS,
};

void read_io_param(){
	uint16_t io_param;
	flash_read(IO_PARAM_START, &io_param, 1);
	printf("io_param:%04x\r\n", io_param);

}

void save_io_param(){
	uint16_t io_param = 18;
	flash_write(IO_PARAM_START, &io_param, 1);
	printf("save io_param\r\n");
}

void get_adc_chan_mode(){
	uint16_t mode; // each bit represent a channel,
	flash_read(ADC_PARAM_START, &mode, 1);

	for(int i = 0; i < 8; i++){
		chan_list[i].mode = (mode>>i)&0x01;
	}

	printf("load ADC param %04x\r\n", mode);

}
void save_adc_chan_mode(){
	uint16_t mode = 0;

	for(int i = 0; i< 8 ; i++){
		mode |= (((uint8_t)chan_list[i].mode) << i);
	}
	;
	printf("save ADC param: %d\r\n", flash_write(ADC_PARAM_START, &mode, 1));
}
void get_btn_mode(){

}
void save_btn_mode(){

}

void get_di_chan_mode(){
	uint16_t modes[8];
	flash_read(ADC_PARAM_START, modes, 8);
	for(int i = 0; i<8; i++){
		di_chan[i].mode = modes[i];
	}
	printf("load di mode\r\n");
}
void save_di_chan_mode(){
	uint16_t modes[8];
	for(int i = 0; i< 8; i++){
		modes[i] = di_chan[i].mode;
	}
	printf("save DI param: %d\r\n", flash_write(ADC_PARAM_START, modes, 8));
}
// RAIN
void save_rain_state(uint16_t mode){
	uint16_t      temp_mode; // each bit represent a channel,
	error_status  status;

	flash_read(RAIN_PARAM_START, &temp_mode, 1);

	if(temp_mode == mode){
		printf("No need to save rain state\r\n");
	}else{
		temp_mode = mode;
		flash_write(RAIN_PARAM_START, &temp_mode, 1);
		printf("save rain state %d\r\n", temp_mode);

//		delay_ms(100);
//
//		flash_read(RAIN_PARAM_START, &temp_mode, 1);
//
//		printf("read after write: %d", temp_mode);
	}


}
void load_rain_state(){
	uint16_t mode; // each bit represent a channel,

	flash_read(RAIN_PARAM_START, &mode, 1);

	printf("Load rain state: %d\r\n", mode);

	if(mode == 0xFFFF){
		mode = 0;
	}

	if(mode > 0){
		set_rain_mode(1, RAIN_MODE_NOTIFY);
	}else{
		set_rain_mode(1, RAIN_MODE_QUERY);
	}
}

void load_state_from_storage(){
	load_rain_state();
}

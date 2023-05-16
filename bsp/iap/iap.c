/*
 * iap.c
 *
 *  Created on: 2023 Feb 28
 *      Author: ruffman
 */



#include "at32f415_board.h"
#include "iap.h"
#include "flash.h"

uint16_t get_update_param(){
	uint16_t val;
	flash_read(IAP_UPGRADE_FLAG_ADDR, &val, 1);
	return val;
}
// 0 is failure
error_status set_update_param(uint16_t flag){
	return flash_write(IAP_UPGRADE_FLAG_ADDR,&flag, 1);
}

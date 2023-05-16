/*
 * flash.h
 *
 *  Created on: 2023 Feb 28
 *      Author: ruffman
 */

#ifndef INCLUDE_IAP_FLASH_H_
#define INCLUDE_IAP_FLASH_H_


#include "at32f415_board.h"

#define FLASH_SIZE    (*((uint32_t*)0x1FFFF7E0))
/* read from at32 flash capacity register(unit:kbyte) */
#define SRAM_SIZE                       32
/* sram size, unit:kbyte */

#define SECTOR_SIZE                     2048

//#define PARMETER_SIZE     10
//#define FLASH_END         0x08040000
//#define PARAMETER_START   (FLASH_END - (0x800*PARMETER_SIZE))
//
//#define IO_PARAM_START       PARAMETER_START
//#define ADC_PARAM_START     (PARAMETER_START +  1 * SECTOR_SIZE)
//#define DI_PARAM_START      (PARAMETER_START +  2 * SECTOR_SIZE)
//#define BTN_PARAM_START     (PARAMETER_START +  3 * SECTOR_SIZE)
//
//#define UPDATE_PARAM_START  (PARAMETER_START +  8 * SECTOR_SIZE)



void flash_2kb_write(uint32_t write_addr, uint8_t *pbuffer);
flag_status flash_upgrade_flag_read(void);

void flash_read(uint32_t read_addr, uint16_t *p_buffer, uint16_t num_read);

error_status flash_write_nocheck(uint32_t write_addr, uint16_t *p_buffer, uint16_t num_write);

error_status flash_write(uint32_t write_addr,uint16_t *p_Buffer, uint16_t num_write);



#endif /* INCLUDE_IAP_FLASH_H_ */

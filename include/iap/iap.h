/*
 * iap.h
 *
 *  Created on: 2023 Feb 28
 *      Author: ruffman
 */

#ifndef INCLUDE_IAP_IAP_H_
#define INCLUDE_IAP_IAP_H_

#include "at32f415_board.h"


#define PARMETER_SIZE     10
#define FLASH_END         0x08040000
#define PARAMETER_START   (FLASH_END - (0x800 * PARMETER_SIZE))

#define IO_PARAM_START       PARAMETER_START
#define ADC_PARAM_START     (PARAMETER_START +  1 * SECTOR_SIZE)
#define DI_PARAM_START      (PARAMETER_START +  2 * SECTOR_SIZE)
#define BTN_PARAM_START     (PARAMETER_START +  3 * SECTOR_SIZE)
#define RAIN_PARAM_START     (PARAMETER_START +  4 * SECTOR_SIZE)

#define UPDATE_PARAM_START  (PARAMETER_START +  8 * SECTOR_SIZE)



/* app starting address */
#define APP_START_ADDR          0x08008000

/* the previous sector of app starting address is iap upgrade flag */
#define IAP_UPGRADE_FLAG_ADDR    (APP_START_ADDR - 0x800)

/* when app received cmd 0x5aa5 from pc-tool, will set up the flag,
indicates that an app upgrade will follow, see iap application note for more details */
// ATK8
#define IAP_UPGRADE_FLAG         0x41544B38
//
//#define HALF_APP_SIZE            (102*1024)
//
//#define APP_STORE_ADDR           (APP_START_ADDR + HALF_APP_SIZE)
//
//
//#define UPDATE_UNNECESSARY      0x0000
//#define UPDATE_TO_APP_START     0xFFFF
//#define UPDATE_TO_APP_STORE     0xFFF0
//#define UPDATE_TO_APP_COPY      0x0001

uint16_t get_update_param();

#endif /* INCLUDE_IAP_IAP_H_ */

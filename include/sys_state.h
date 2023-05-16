/*
 * sys_state.h
 *
 *  Created on: 2023 Feb 22
 *      Author: ruffman
 */

#ifndef INCLUDE_SYS_STATE_H_
#define INCLUDE_SYS_STATE_H_

#include "at32f415_board.h"
#include "at32f415_clock.h"
#include "FreeRTOS.h"
#include "task.h"

enum SYS_STATE_TYPE{
	BOOT,
	NORMAL,
	DEEPSLEEP,
	UPGRADING
};

enum UPGRADE{
	NEED,
	NEEDLESS,
};

struct MCU_SYSTEM{
	 enum SYS_STATE_TYPE state;
	 enum UPGRADE need_upgrade;
};

#endif /* INCLUDE_SYS_STATE_H_ */

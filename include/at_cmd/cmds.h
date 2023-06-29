/*
 * cmds.h
 *
 *  Created on: 2023 Feb 21
 *      Author: ruffman
 */

#ifndef INCLUDE_AT_CMD_CMDS_CMDS_H_
#define INCLUDE_AT_CMD_CMDS_CMDS_H_

#include "task_conf.h"

#include "at32f415_board.h"
#include "at32f415_clock.h"
#include "FreeRTOS.h"
#include "task.h"


#define AT_ERROR_POSITION   "100"
#define AT_ERROR_PARAMETER  "101"
#define AT_ERROR_EXEC       "102"
#define AT_ERROR_UNKNOWN    "103"

// AT
void cmd_at_exec(void);


// VERSION
void cmd_version_exec(void);
void cmd_version_read(void);
void cmd_version_test(void);
void cmd_version_write(char*str, int len);

// RESTORE
void cmd_restore_exec(void);

// RST
#define RST_DELAY  1000
void cmd_rst_exec();

// CDATE
void cmd_cdate_read();
void cmd_cdate_write(char* str, int len);

// RESTORE
void cmd_restore_exec();

// IOVO
void cmd_iovo_write(char* str, int len);
void cmd_iovo_read();

// IORLY
void cmd_iorly_write(char* str, int len);
void cmd_iorly_read();

// ADC
void cmd_ioadcpwr_write(char* str, int len);
void cmd_ioadcmode_read();
void cmd_ioadcmode_write(char* str, int len);
void cmd_ioadcread_write(char* str, int len);
void cmd_invol_read();

// DI
void cmd_iodimode_read();
void cmd_iodimode_write(char* str, int len);
void cmd_iodicnt_write(char* str, int len);
void cmd_iodiread_write(char* str, int len);


// DO
void  cmd_iodo_write(char* str, int len);

// BTN
void cmd_iobtnsub_read();
void cmd_iobtnsub_write(char*str , int len);
void cmd_iobtnunsub_write(char*str , int len);


// RAIN
void cmd_iorainmode_read();
void cmd_iorainmode_write(char*str , int len);
void cmd_ioraincnt_write(char*str , int len);
void cmd_iorainread_write(char*str , int len);

// cgsn
void cmd_cgsn();

// LED
void cmd_ioledonoff_write(char* str, int len);
void cmd_ioledonoff_read();
void cmd_ioledblink_write(char* str, int len);
void cmd_ioledblink_read();


#endif /* INCLUDE_AT_CMD_CMDS_CMDS_H_ */

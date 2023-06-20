/**
  **************************************************************************
  * @file     main.c
  * @version  v2.0.5
  * @date     2022-05-20
  * @brief    main program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#include "at32f415_board.h"
#include "at32f415_clock.h"
#include "FreeRTOS.h"
#include "task.h"

#include "task_conf.h"


/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
int main(void)
{
	uint8_t data[2];
  /* config vector table offset */
  nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x8000);


  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  system_clock_config();

  at32_board_init();

  //
  at32_led_on(LED4);

//
//  data[0] = 0x0E;
//  write_EEPROM_DC(data, 1);
//
//  data[0] = 0x0F;
//  write_EEPROM_ADC(data, 1);

/*
  while(1){
	  printf("shining LED4\n");
	  delay_sec(1);
	  at32_led_off(LED4);
	  delay_sec(1);
	  at32_led_on(LED4);

//	  update_eeprom_param();
	  if(read_EEPROM_DC(data, 1) == 0){
		  printf("read DC: %02X\n", data[0]);
	  }
	  if(read_EEPROM_ADC(data, 1) == 0){
		  printf("read ADC: %02X\n", data[0]);
	  }

  }

*/

  /* enter critical */
  taskENTER_CRITICAL();

  init_print_log_task();
  init_at_send_task();
  init_main_task();
  init_at_parser_task();


  /* exit critical */
  taskEXIT_CRITICAL();

  /* start scheduler */
  vTaskStartScheduler();
}

/**
  * @}
  */
void vApplicationIdleHook( void )
{
	wdt_reload();
}
/**
  * @}
  */

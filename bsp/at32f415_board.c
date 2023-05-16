/**
  **************************************************************************
  * @file     at32f415_board.c
  * @version  v2.0.5
  * @date     2022-05-20
  * @brief    set of firmware functions to manage leds and push-button.
  *           initialize delay function.
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



/** @addtogroup AT32F415_board
  * @{
  */

/** @defgroup BOARD
  * @brief onboard periph driver
  * @{
  */



char version[]="1.0.2";
char model[] = "IOEXT_AT32F415";
char date[] = "2023.02.10";

void print_welcome(){
	printf("%s, Firmware v%s\r\n", model, version);
	printf("%s\r\n", date);
	printf("AT32F415\r\n");
}

/**
  * @brief  board initialize interface init led and button
  * @param  none
  * @retval none
  */
void at32_board_init()
{
  /* initialize delay function */
  delay_init();

  /* configure led in at_start_board */
//  at32_led_init(LED2);
////  at32_led_init(LED3);
  at32_led_init(LED4);
//  at32_led_off(LED2);
//  at32_led_off(LED3);
  at32_led_off(LED4);



  /* init usart1 */
  uart_print_init(115200);

  print_welcome();

  init_d1_uart();

  rtc_clock_init();

  init_RS232_RS485_pwr_gpio();

  init_relay_gpio();

  init_adc_power_gpio();

  init_adc();

  init_di_gpio();

  init_do_gpio();


  /* configure button in at_start board */
  user_button_gpio_init();
  user_button_exint_init();
  user_button_timer1_init();


  load_state_from_storage();


  init_rain_gpio();
  init_rain_exint();

  init_i2c_2();

  init_d1_power_gpio();

  init_wdt();

}




/**
  * @}
  */

/**
  * @}
  */


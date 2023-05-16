/*
 * mcu_button.c
 *
 *  Created on: 2023 Feb 21
 *      Author: ruffman
 */

#include "at32f415_board.h"
#include "task_conf.h"

uint8_t           button_changed = 0;




//#define DELAY                            100
//#define FAST                             1
//#define SLOW                             4

//uint8_t g_speed = FAST;

/**
  * @brief  configure button gpio
  * @param  button: specifies the button to be configured.
  * @retval none
  */
void user_button_gpio_init(void)
{
  gpio_init_type gpio_init_struct;

  /* enable the button clock */
  crm_periph_clock_enable(USER_BUTTON_CRM_CLK, TRUE);

  /* set default parameter */
  gpio_default_para_init(&gpio_init_struct);

  /* configure button pin as input with pull-up/pull-down */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pins = USER_BUTTON_PIN;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;

  gpio_init(USER_BUTTON_PORT, &gpio_init_struct);
}
/**
  * @brief  configure button exint
  * @param  none
  * @retval none
  */
void user_button_exint_init(void)
{
  exint_init_type exint_init_struct;

  crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(USER_BUTTON_CRM_CLK, TRUE);

  gpio_exint_line_config(USER_BUTTON_PORT_SOURCE, USER_BUTTON_SOURCE);

  exint_default_para_init(&exint_init_struct);
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_select = EXINT_LINE_2;
  exint_init_struct.line_polarity = EXINT_TRIGGER_BOTH_EDGE;
  exint_init(&exint_init_struct);

  exint_interrupt_enable(EXINT_LINE_2, TRUE);

  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(EXINT2_IRQn, 4, 0);
}
/**
  * @brief  returns the selected button state
  * @param  none
  * @retval the button gpio pin value
  */
//uint8_t user_button_state(void)
//{
//  return gpio_input_data_bit_read(USER_BUTTON_PORT, USER_BUTTON_PIN);
//}

/**
  * @brief  returns which button have press down
  * @param  none
  * @retval the button have press down
  */
//button_type user_button_press()
//{
//  static uint8_t pressed = 1;
//  /* get button state in at_start board */
//  if((pressed == 1) && (user_button_state() != RESET))
//  {
//    /* debounce */
//    pressed = 0;
//    delay_ms(10);
//    if(user_button_state() != RESET)
//      return USER_BUTTON;
//  }
//  else if(user_button_state() == RESET)
//  {
//    pressed = 1;
//  }
//  return NO_BUTTON;
//}

/**
  * @brief  exint2 interrupt handler
  * @param  none
  * @retval none
  */
void EXINT2_IRQHandler(void)
{
	if (exint_flag_get(EXINT_LINE_2) != RESET) {
		/* clear interrupt pending bit */
		exint_flag_clear(EXINT_LINE_2);
//
//		at32_led_toggle(LED4);

		button_changed = 1;

//		if(button_state == STATE_BUTTON_RELEASED){
//			/* check input pin state */
//			if (RESET == gpio_input_data_bit_read(
//					USER_BUTTON_PORT,
//					USER_BUTTON_PIN)) {
//				button_state = STATE_BUTTON_PRESSED;
//			}
//		}else{
//			if (SET == gpio_input_data_bit_read(
//					USER_BUTTON_PORT,
//					USER_BUTTON_PIN)) {
//				button_state = STATE_BUTTON_RELEASED;
//			}
//
//		}

		/* check input pin state */
//		if (SET == gpio_input_data_bit_read(
//				USER_BUTTON_PORT,
//				USER_BUTTON_PIN)) {
//
//		}
	}
}

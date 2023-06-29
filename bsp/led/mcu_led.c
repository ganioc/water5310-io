/*
 * mcu_led.c
 *
 *  Created on: 2023 Feb 21
 *      Author: ruffman
 */


#include "at32f415_board.h"

/* at-start led resouce array */
gpio_type *led_gpio_port[LED_NUM]        = {LED2_GPIO, LED3_GPIO, LED4_GPIO};
uint16_t led_gpio_pin[LED_NUM]           = {LED2_PIN, LED3_PIN, LED4_PIN};
crm_periph_clock_type led_gpio_crm_clk[LED_NUM] = {LED2_GPIO_CRM_CLK, LED3_GPIO_CRM_CLK, LED4_GPIO_CRM_CLK};



struct LED_STAUTS led_status[LED_NUM]={0};

/**
  * @brief  configure led gpio
  * @param  led: specifies the led to be configured.
  * @retval none
  */
void at32_led_init(led_type led)
{
  gpio_init_type gpio_init_struct;

  /* enable the led clock */
  crm_periph_clock_enable(led_gpio_crm_clk[led], TRUE);

  /* set default parameter */
  gpio_default_para_init(&gpio_init_struct);

  /* configure the led gpio */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_init_struct.gpio_pins = led_gpio_pin[led];
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(led_gpio_port[led], &gpio_init_struct);
}

/**
  * @brief  turns selected led on.
  * @param  led: specifies the led to be set on.
  *   this parameter can be one of following parameters:
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval none
  */
void at32_led_on(led_type led)
{
  if(led > (LED_NUM - 1))
    return;
  if(led_gpio_pin[led])
    led_gpio_port[led]->scr = led_gpio_pin[led];
}

/**
  * @brief  turns selected led off.
  * @param  led: specifies the led to be set off.
  *   this parameter can be one of following parameters:
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval none
  */
void at32_led_off(led_type led)
{
  if(led > (LED_NUM - 1))
    return;
  if(led_gpio_pin[led])
    led_gpio_port[led]->clr = led_gpio_pin[led];
}

/**
  * @brief  turns selected led toggle.
  * @param  led: specifies the led to be set off.
  *   this parameter can be one of following parameters:
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval none
  */
void at32_led_toggle(led_type led)
{
  if(led > (LED_NUM - 1))
    return;
  if(led_gpio_pin[led])
    led_gpio_port[led]->odt ^= led_gpio_pin[led];
}
void at32_led_set_onoff_state(led_type led, uint16_t onOff){
	struct LED_STAUTS *stat = &led_status[led];

	stat->no = led;
	stat->onOff = onOff;
	stat->mode = 0;
}
void at32_led_set_onoff(led_type led, uint8_t onOff){
	// if state is not
	uint8_t state = gpio_read(led_gpio_port[led], led_gpio_pin[led]);

	if(state != onOff){
		if(onOff > 0){
			at32_led_on(led);
		}else{
			at32_led_off(led);
		}
	}
}
uint8_t at32_led_get_onoff(led_type led){
	return (uint8_t)led_status[led].onOff;
}
/*
 * onTime : in ms
 * offTime: in ms
 * repeatCnt: -1, forever; >1,
 */
void at32_led_set_blink_state(led_type led,uint16_t onTime, uint16_t offTime, uint16_t repeatCnt){
	struct LED_STAUTS *stat = &led_status[led];

	if(onTime <= 0 || offTime <= 0){
		at32_led_set_onoff(led, (uint8_t)0);
	}else{

		stat->repeatCnt = (repeatCnt == 0)? -1: repeatCnt;
		stat->onTime = ((onTime/BUTTON_TIMER_PERIDO) < 1)?1:(onTime/BUTTON_TIMER_PERIDO);
		stat->offTime = ((offTime/BUTTON_TIMER_PERIDO) < 1)?1:(offTime/BUTTON_TIMER_PERIDO);

		stat->repeatCntCounter = stat->repeatCnt;
		stat->onTimeCounter = stat->onTime;
		stat->offTimeCounter = stat->offTime;

		stat->no = led;
		stat->state = LED_S_START;
		stat->mode = 1;
	}

}
struct LED_STAUTS at32_led_get_status(led_type led){
	return led_status[led];
}


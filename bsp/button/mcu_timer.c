/*
 * timer.c
 *
 *  Created on: 2023 Feb 20
 *      Author: ruffman
 */
#include "at32f415_board.h"
#include "task_conf.h"

#include <stdlib.h>
#include <string.h>

// to use timer1 for button press detection,

#define SCAN_INTERVAL     50

crm_clocks_freq_type crm_clocks_freq_struct = {0};

/// 9999 -  1 second
// uint16_t TIMER1_COUNT_VAL = 999; // 100 ms
uint16_t TIMER1_COUNT_VAL = 499;   // 50ms
//uint16_t TIMER1_COUNT_VAL = 333; // 30 ms
//uint16_t TIMER1_COUNT_VAL = 200; // 20 ms

enum BUTTON_STATE button_diagram_state = STATE_BUTTON_RELEASED;
uint16_t        counter                = 0;
uint16_t        click_num              = 0;
static  char    str_temp[32];


enum RAINDROP_STATE  raindrop_state  = RAIN_STATE_DUMMY;


struct BUTTON_EVENT_NAME btns[4] = {
		{ id: 0,  enabled: 0, name: "pressed", interval: 0},
		{ id: 1,  enabled: 0, name: "released", interval: 0},
		{ id: 2,
				enabled: 1,
				name: "click",
				interval: USER_BUTTON_CLICK_INTERVAL},
		{ id: 3,
				enabled: 0,
				name: "long",
				interval: USER_BUTTON_LONG_INTERVAL}
};

extern uint32_t rain_count;
extern enum RAIN_MODE   rain_mode;

void user_button_enable_long_click(){
	// save to flash,eeprom
	btns[3].enabled = 1;
}
uint8_t user_button_get_click_sub(){
	return btns[2].enabled;
}
uint8_t user_button_get_long_sub(){
	return btns[3].enabled;
}
void user_button_disable_long_click(){
	btns[3].enabled = 0;
}

uint16_t get_short_press_dur(){
	return btns[2].interval/SCAN_INTERVAL;
}
uint16_t get_long_press_dur(){
	return btns[3].interval/SCAN_INTERVAL;
}


extern  uint8_t      button_changed;

void user_button_timer1_init(void){
	/* get system clock */
	crm_clocks_freq_get(&crm_clocks_freq_struct);
	/* enable tmr1 clock */
	crm_periph_clock_enable(CRM_TMR1_PERIPH_CLOCK, TRUE);

	/* tmr1 configuration */
	/* time base configuration */
	/* systemclock/12000/10000 = 1hz */
	tmr_base_init(TMR1,
			TIMER1_COUNT_VAL,
			(crm_clocks_freq_struct.ahb_freq / 10000) - 1);
	tmr_cnt_dir_set(TMR1, TMR_COUNT_UP);

	/* overflow interrupt enable */
	tmr_interrupt_enable(TMR1, TMR_OVF_INT, TRUE);
	/* tmr1 overflow interrupt nvic init */
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
	nvic_irq_enable(TMR1_OVF_TMR10_IRQn, 5 , 0);
	/* enable tmr1 */
	tmr_counter_enable(TMR1, TRUE);
}


/**
  * @brief  this function handles timer1 overflow handler.
  * @param  none
  * @retval none
  */
void TMR1_OVF_TMR10_IRQHandler(void)
{
  flag_status  button_status;

  if(tmr_flag_get(TMR1, TMR_OVF_FLAG) != RESET)
  {
    tmr_flag_clear(TMR1, TMR_OVF_FLAG);

    // raindrop state
    switch(raindrop_state){
    case RAIN_STATE_DUMMY:
    	break;
    case RAIN_STATE_0:
    	raindrop_state = RAIN_STATE_1;
    	break;
    case RAIN_STATE_1:

    	sprintf(str_temp,
    	    	"\r\n+IORAINCNT:1,%d\r\n", ++rain_count);

    	if(rain_mode == RAIN_MODE_NOTIFY){
    		send_to_at_queue_fromISR(str_temp, strlen(str_temp));
    	}

    	raindrop_state = RAIN_STATE_DUMMY;
    	break;
    default:
    	break;

    }


    // at32_led_toggle(LED3);

    switch(button_diagram_state){
    case STATE_BUTTON_RELEASED:
    	if(button_changed == 1){
    		button_changed = 0;
    		counter = 0;
    		click_num = 0;
    		button_diagram_state = STATE_BUTTON_PRESSED;

//    		sprintf(str_temp,"\r\n+IOBTNEVT:1,\"pressed\"\r\n");
//    		send_to_at_queue_fromISR(str_temp, strlen(str_temp));
    	}
    	break;
    case STATE_BUTTON_PRESSED:
    	counter++;
    	if(counter >= get_long_press_dur() ){
    		if(click_num > 0){
    			sprintf(str_temp,
    					"\r\n+IOBTNEVT:1,\"click\",%d\r\n", click_num + 1);
    			send_to_at_queue_fromISR(str_temp, strlen(str_temp));
    			click_num = 0;
    		}
//    		sprintf(str_temp,
//    				"\r\n+IOBTNEVT:1,\"long\",%d\r\n", counter * SCAN_INTERVAL);
//    		send_to_at_queue_fromISR(str_temp, strlen(str_temp));

    		//counter = 0;

    		if(btns[3].enabled == 1){
        		button_diagram_state = STATE_BUTTON_LONG;
    		}
    		else{
    			counter = 0;
    		}
    	}
    	else if(button_changed == 1){
    		button_changed = 0;
    		counter = 0;
    		button_diagram_state = STATE_BUTTON_SHORT;
    	}
    	break;
    case STATE_BUTTON_SHORT:
    	counter++;
    	if(counter >= get_short_press_dur() ){
    		sprintf(str_temp,
    				"\r\n+IOBTNEVT:1,\"click\",%d\r\n", click_num + 1);
    		send_to_at_queue_fromISR(str_temp, strlen(str_temp));
    		button_diagram_state = STATE_BUTTON_RELEASED;

//    		sprintf(str_temp,"\r\n+IOBTNEVT:1,\"released\"\r\n");
//    		send_to_at_queue_fromISR(str_temp, strlen(str_temp));
    	}else if(button_changed == 1){
    		button_changed = 0;
    		counter = 0;
    		click_num++;

    		button_diagram_state = STATE_BUTTON_PRESSED;
    	}
    	break;
    case STATE_BUTTON_LONG:
    	counter++;
    	if(button_changed == 1 ||
    			(SET == gpio_input_data_bit_read(
				USER_BUTTON_PORT,
				USER_BUTTON_PIN))){
    		button_changed = 0;

    		sprintf(str_temp,
    				"\r\n+IOBTNEVT:1,\"long\",%d\r\n", counter * SCAN_INTERVAL);
    		send_to_at_queue_fromISR(str_temp, strlen(str_temp));

    		counter = 0;
    		button_diagram_state = STATE_BUTTON_RELEASED;

//    		sprintf(str_temp,"\r\n+IOBTNEVT:1,\"released\"\r\n");
//    		send_to_at_queue_fromISR(str_temp, strlen(str_temp));
    	}

    	break;
    default:

    	break;
    }
  }
}


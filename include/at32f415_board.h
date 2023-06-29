/**
  **************************************************************************
  * @file     at32f415_board.h
  * @version  v2.0.5
  * @date     2022-05-20
  * @brief    header file for at-start board. set of firmware functions to
  *           manage leds and push-button. initialize delay function.
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

#ifndef __AT32F415_BOARD_H
#define __AT32F415_BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "at32f415.h"

/** @addtogroup AT32F415_board
  * @{
  */

/** @addtogroup BOARD
  * @{
  */

/** @defgroup BOARD_pins_definition
  * @{
  */

/**
  * this header include define support list:
  * 1. at-start-f415 v1.x board
  * if define AT_START_F415_V1, the header file support at-start-f415 v1.x board
  */

#if !defined (AT_START_F415_V1)
#error "please select first the board at-start device used in your application (in at32f415_board.h file)"
#endif

/******************** define led ********************/
typedef enum
{
  LED2                                   = 0,
  LED3                                   = 1,
  LED4                                   = 2
} led_type;

#define LED_NUM                          3

#if defined (AT_START_F415_V1)
#define LED2_PIN                         GPIO_PINS_2
#define LED2_GPIO                        GPIOC
#define LED2_GPIO_CRM_CLK                CRM_GPIOC_PERIPH_CLOCK

#define LED3_PIN                         GPIO_PINS_3
#define LED3_GPIO                        GPIOC
#define LED3_GPIO_CRM_CLK                CRM_GPIOC_PERIPH_CLOCK

#define LED4_PIN                         GPIO_PINS_12
#define LED4_GPIO                        GPIOA
#define LED4_GPIO_CRM_CLK                CRM_GPIOA_PERIPH_CLOCK
#endif


struct LED_STAUTS{
	uint16_t mode; // 0:constant; 1:blink
	uint16_t no;  // channel number
	uint16_t onOff;
	uint16_t onTime;
	uint16_t offTime;
	int16_t repeatCnt;
	uint16_t onTimeCounter;
	uint16_t offTimeCounter;
	uint16_t repeatCntCounter;// -1, for ever; 0, stop, same as constant, no need to use 'mode',
	uint16_t state;
};
enum LED_TRANSFER_STATE{

	LED_S_CONSTANT=0,
	LED_S_START,
	LED_S_ON,
	LED_S_OFF
};

struct LED_STAUTS at32_led_get_status(led_type led);
void at32_led_set_blink_state(led_type led,uint16_t onTime, uint16_t offTime, uint16_t repeatCnt);
void at32_led_set_onoff(led_type led, uint8_t onOff);
uint8_t at32_led_get_onoff(led_type led);
void at32_led_set_onoff_state(led_type led, uint16_t onOff);

/**************** define print uart ******************/
#define PRINT_UART                       USART3
#define PRINT_UART_CRM_CLK               CRM_USART3_PERIPH_CLOCK
#define PRINT_UART_TX_PIN                GPIO_PINS_10
#define PRINT_UART_TX_GPIO               GPIOB
#define PRINT_UART_TX_GPIO_CRM_CLK       CRM_GPIOB_PERIPH_CLOCK





/******************* ERTC *****************************/
#define ERTC_BPR_DT_NUMBER   5
#define ERTC_MAGIC           0x1234


/*******************D1 UART ***************************/
#define D1_UART                       USART1
#define D1_UART_CRM_CLK               CRM_USART1_PERIPH_CLOCK
#define D1_UART_TX_PIN                GPIO_PINS_9
#define D1_UART_RX_PIN                GPIO_PINS_10
#define D1_UART_TX_GPIO               GPIOA
#define D1_UART_TX_GPIO_CRM_CLK       CRM_GPIOA_PERIPH_CLOCK
#define D1_UART_IRQn                  USART1_IRQn


/**
  * @}
  */

/** @defgroup BOARD_exported_functions
  * @{
  */

/******************** functions ********************/
void at32_board_init(void);

/* led operation function */
void at32_led_init(led_type led);
void at32_led_on(led_type led);
void at32_led_off(led_type led);
void at32_led_toggle(led_type led);
void at32_led_check_pattern(led_type led);

/* button operation function */

/******************* define button *******************/
typedef enum
{
  USER_BUTTON                            = 0,
  NO_BUTTON                              = 1
} button_type;

enum BUTTON_EVENT{
	PRESSED     = 0,
	RELEASED    = 1,
	CLICK       = 2,
	LONG_CLICK  = 3,
};

struct BUTTON_EVENT_NAME{
	uint8_t    id;
	uint8_t enabled;
	char name[10];
	uint16_t   interval;
};

#define USER_BUTTON_PIN                  GPIO_PINS_2
#define USER_BUTTON_PORT                 GPIOB
#define USER_BUTTON_CRM_CLK              CRM_GPIOB_PERIPH_CLOCK
#define USER_BUTTON_PORT_SOURCE          GPIO_PORT_SOURCE_GPIOB
#define USER_BUTTON_SOURCE               GPIO_PINS_SOURCE2

#define USER_BUTTON_CLICK_INTERVAL    150
#define USER_BUTTON_LONG_INTERVAL     800

#define BUTTON_TIMER_PERIDO           50

enum BUTTON_STATE{
	STATE_BUTTON_RELEASED = 0,
	STATE_BUTTON_PRESSED  = 1,
	STATE_BUTTON_SHORT    = 2,
	STATE_BUTTON_LONG     = 3
};

void user_button_gpio_init(void);
void user_button_exint_init(void);
void user_button_timer1_init(void);
void user_button_enable_long_click();
void user_button_disable_long_click();
uint8_t user_button_get_click_sub();
uint8_t user_button_get_long_sub();

/* delay function */
void delay_init(void);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);
void delay_sec(uint16_t sec);

/* printf uart init function */
void uart_print_init(uint32_t baudrate);
void print_welcome();

// D1 UART
void init_d1_uart();

//  RTC
void rtc_clock_init();

/*  gpio init , control */
void init_gpio_output(
		crm_periph_clock_type crm_clock,
		gpio_type* port,
		uint16_t pin,
		gpio_pull_type pull);
void init_gpio_input(
		crm_periph_clock_type crm_clock,
		gpio_type* port,
		uint16_t pin,
		gpio_pull_type pull);
void gpio_on(gpio_type* port, uint16_t pin);
void gpio_off(gpio_type* port, uint16_t pin);
void gpio_toggle(gpio_type* port, uint16_t pin);
uint8_t gpio_read(gpio_type* port, uint16_t pin);


/*  power control  */
enum PWR_CTRL_NUM {
	PWR_CTRL_ADC=1,
	PWR_CTRL_SDI,
	PWR_CTRL_485,
	PWR_CTRL_232,
	PWR_CTRL_VCCOUT
};
#define VCCOUT_1_POWER_PIN       GPIO_PINS_4
#define VCCOUT_1_POWER_PORT      GPIOF
#define VCCOUT_1_POWER_CRM_CLOCK CRM_GPIOF_PERIPH_CLOCK

#define SDI_1_POWER_PIN       GPIO_PINS_5
#define SDI_1_POWER_PORT      GPIOC
#define SDI_1_POWER_CRM_CLOCK CRM_GPIOC_PERIPH_CLOCK

#define RS232_1_POWER_PIN       GPIO_PINS_5
#define RS232_1_POWER_PORT      GPIOF
#define RS232_1_POWER_CRM_CLOCK CRM_GPIOF_PERIPH_CLOCK

#define RS485_1_POWER_PIN       GPIO_PINS_4
#define RS485_1_POWER_PORT      GPIOC
#define RS485_1_POWER_CRM_CLOCK CRM_GPIOC_PERIPH_CLOCK

void init_RS232_RS485_pwr_gpio();
void RS232_RS485_pwr_ctrl(uint8_t channel, uint8_t onoff);
uint8_t RS232_RS485_get_gpio_status(uint8_t channel);

// RELAY
#define RELAY_1_PIN         GPIO_PINS_0
#define RELAY_1_PORT        GPIOC
#define RELAY_1_CRM_CLOCK   CRM_GPIOC_PERIPH_CLOCK

#define RELAY_2_PIN         GPIO_PINS_1
#define RELAY_2_PORT        GPIOC
#define RELAY_2_CRM_CLOCK   CRM_GPIOC_PERIPH_CLOCK

#define RELAY_3_PIN         GPIO_PINS_2
#define RELAY_3_PORT        GPIOC
#define RELAY_3_CRM_CLOCK   CRM_GPIOC_PERIPH_CLOCK

#define RELAY_4_PIN         GPIO_PINS_3
#define RELAY_4_PORT        GPIOC
#define RELAY_4_CRM_CLOCK   CRM_GPIOC_PERIPH_CLOCK

void init_relay_gpio();
void relay_ctrl(uint8_t channel, uint8_t onoff);
uint8_t relay_ctrl_get_status(uint8_t channel);


// ADC
#define ADC_POWER_PIN          GPIO_PINS_1
#define ADC_POWER_PORT         GPIOB
#define ADC_POWER_CRM_CLOCK    CRM_GPIOB_PERIPH_CLOCK

void init_adc_power_gpio();
void enable_adc_power();
void disable_adc_power();
void adc_power_ctrl(uint8_t onoff);

enum ADC_MODE{
	VOLTAGE = 0,
	CURRENT = 1
};

struct ADC_CHAN {
	uint8_t  id;
	enum ADC_MODE mode;
};

#define ADC_CHAN_PORT       GPIOA
#define ADC_CHAN_CRM_CLOCK  CRM_GPIOA_PERIPH_CLOCK

#define ADC_CHAN_0_PIN      GPIO_PINS_0
#define ADC_CHAN_1_PIN      GPIO_PINS_1
#define ADC_CHAN_2_PIN      GPIO_PINS_2
#define ADC_CHAN_3_PIN      GPIO_PINS_3
#define ADC_CHAN_4_PIN      GPIO_PINS_4
#define ADC_CHAN_5_PIN      GPIO_PINS_5
#define ADC_CHAN_6_PIN      GPIO_PINS_6
#define ADC_CHAN_7_PIN      GPIO_PINS_7

#define ADC_INVOL_PORT       GPIOB
#define ADC_INVOL_CRM_CLOCK  CRM_GPIOB_PERIPH_CLOCK
#define ADC_INVOL_PIN        GPIO_PINS_0

void adc_mode_set(uint8_t channel, uint8_t mode);
uint8_t adc_mode_get(uint8_t channel);
void init_adc();
void adc_get(uint8_t channel, uint16_t * v_ref, uint16_t *val);
enum ADC_MODE adc_get_mode(uint8_t channel);
void cmd_invol_read();

// DI
#define DI_1_PIN         GPIO_PINS_3
#define DI_1_PORT        GPIOB
#define DI_1_CRM_CLOCK   CRM_GPIOB_PERIPH_CLOCK

#define DI_2_PIN         GPIO_PINS_4
#define DI_2_PORT        GPIOB
#define DI_2_CRM_CLOCK   CRM_GPIOB_PERIPH_CLOCK

#define DI_3_PIN         GPIO_PINS_5
#define DI_3_PORT        GPIOB
#define DI_3_CRM_CLOCK   CRM_GPIOB_PERIPH_CLOCK

#define DI_4_PIN         GPIO_PINS_6
#define DI_4_PORT        GPIOB
#define DI_4_CRM_CLOCK   CRM_GPIOB_PERIPH_CLOCK

#define DI_5_PIN         GPIO_PINS_7
#define DI_5_PORT        GPIOB
#define DI_5_CRM_CLOCK   CRM_GPIOB_PERIPH_CLOCK

#define DI_6_PIN         GPIO_PINS_8
#define DI_6_PORT        GPIOB
#define DI_6_CRM_CLOCK   CRM_GPIOB_PERIPH_CLOCK

#define DI_7_PIN         GPIO_PINS_9
#define DI_7_PORT        GPIOB
#define DI_7_CRM_CLOCK   CRM_GPIOB_PERIPH_CLOCK

#define DI_8_PIN         GPIO_PINS_13
#define DI_8_PORT        GPIOC
#define DI_8_CRM_CLOCK   CRM_GPIOC_PERIPH_CLOCK

enum DI_MODE{
	STATUS_QUERY = 0,
	STATUS_CHANGE_NOTIFY = 1,
	COUNTING_QUERY = 2,
	COUNTING_CHANGE_NOTIFY = 3,
};

struct DI_CHAN{
	uint8_t id;
	enum DI_MODE mode;
	uint16_t  count;
	uint16_t  value;
};

void init_di_gpio();
uint8_t di_mode_get(uint8_t channel);
void di_mode_set(uint8_t channel, uint8_t mode);
void di_count_set(uint8_t channel, uint16_t count);
void di_count_get(uint8_t channel, uint8_t*mode, uint16_t*count);

// DO
#define DO_1_PIN         GPIO_PINS_12
#define DO_1_PORT        GPIOB
#define DO_1_CRM_CLOCK   CRM_GPIOB_PERIPH_CLOCK

#define DO_2_PIN         GPIO_PINS_13
#define DO_2_PORT        GPIOB
#define DO_2_CRM_CLOCK   CRM_GPIOB_PERIPH_CLOCK

#define DO_3_PIN         GPIO_PINS_14
#define DO_3_PORT        GPIOB
#define DO_3_CRM_CLOCK   CRM_GPIOB_PERIPH_CLOCK

#define DO_4_PIN         GPIO_PINS_15
#define DO_4_PORT        GPIOB
#define DO_4_CRM_CLOCK   CRM_GPIOB_PERIPH_CLOCK


#define DO_5_PIN         GPIO_PINS_6
#define DO_5_PORT        GPIOC
#define DO_5_CRM_CLOCK   CRM_GPIOC_PERIPH_CLOCK

#define DO_6_PIN         GPIO_PINS_7
#define DO_6_PORT        GPIOC
#define DO_6_CRM_CLOCK   CRM_GPIOC_PERIPH_CLOCK

#define DO_7_PIN         GPIO_PINS_8
#define DO_7_PORT        GPIOC
#define DO_7_CRM_CLOCK   CRM_GPIOC_PERIPH_CLOCK

#define DO_8_PIN         GPIO_PINS_9
#define DO_8_PORT        GPIOC
#define DO_8_CRM_CLOCK   CRM_GPIOC_PERIPH_CLOCK

#define DO_CHANNEL_NUM   8


void init_do_gpio();
void do_ctrl(uint8_t channel, uint8_t onoff);

// RAIN SENSOR
#define RAIN_PIN         GPIO_PINS_8
#define	RAIN_PORT        GPIOA
#define RAIN_CRM_CLOCK   CRM_GPIOA_PERIPH_CLOCK

#define RAIN_PULSE_PIN         GPIO_PINS_11
#define	RAIN_PULSE_PORT        GPIOA
#define RAIN_PULSE_CRM_CLOCK   CRM_GPIOA_PERIPH_CLOCK

enum RAIN_MODE{
	RAIN_MODE_QUERY = 0,
	RAIN_MODE_NOTIFY = 1
};

enum RAINDROP_STATE {
	RAIN_STATE_DUMMY = 0,
	RAIN_STATE_0 = 1,
	RAIN_STATE_1 = 2
};

void init_rain_gpio();
void init_rain_exint();
uint32_t get_rain_count();
uint8_t get_rain_mode();
void set_rain_mode(uint8_t channel, uint8_t mode);
void set_rain_count(uint8_t channel, uint32_t count);

// I2C, EEPROM
//#define I2C_1_SCL_PIN         GPIO_PINS_6
//#define I2C_1_PORT            GPIOF
//#define I2C_1_CRM_CLOCK       CRM_GPIOF_PERIPH_CLOCK
//
//#define I2C_1_SDA_PIN         GPIO_PINS_7

//#define I2Cx_PORT                        I2C2
//#define I2Cx_CLK                         CRM_I2C2_PERIPH_CLOCK

#define I2C1_SCL_PIN                     GPIO_PINS_6
#define I2C1_SCL_GPIO_PORT               GPIOF
#define I2C1_SCL_GPIO_CLK                CRM_GPIOF_PERIPH_CLOCK
#define I2C1_SCL_PIN_MUX_NUM             GPIO_MUX_2

#define I2C1_SDA_PIN                     GPIO_PINS_7
#define I2C1_SDA_GPIO_PORT               GPIOF
#define I2C1_SDA_GPIO_CLK                CRM_GPIOF_PERIPH_CLOCK

// #define I2Cx_SPEED                       100000
#define I2C1_SPEED                       100000
#define I2C1_ADDRESS                     0xA0
#define EEPROM_ADDRESS                   0xA0
//#define C64_ADDRESS                      0xAE

#define I2C1_PORT                        I2C1
#define I2C1_CLK                         CRM_I2C1_PERIPH_CLOCK

//#define I2Cx_DMA_CLK                     CRM_DMA1_PERIPH_CLOCK
//#define I2Cx_DMA_TX_CHANNEL              DMA1_CHANNEL4
//#define I2Cx_DMA_TX_IRQn                 DMA1_Channel4_IRQn
//
//#define I2Cx_DMA_RX_CHANNEL              DMA1_CHANNEL5
//#define I2Cx_DMA_RX_IRQn                 DMA1_Channel5_IRQn
//
//#define I2Cx_EVT_IRQn                    I2C1_EVT_IRQn
//#define I2Cx_ERR_IRQn                    I2C1_ERR_IRQn


void init_i2c_2();
void update_eeprom_param();

// EEPROM,
// parameters to save in the EEPROM,
#define EEPROM_DC_ON               0x0
#define EEPROM_ADC_ON              0x1

int read_EEPROM_DC(uint8_t *data, int len);
int read_EEPROM_ADC(uint8_t *data, int len);
int write_EEPROM_DC(uint8_t *data, int len);
int write_EEPROM_ADC(uint8_t *data, int len);

// D1 power

#define D1_POWER_PIN                     GPIO_PINS_15
#define D1_POWER_GPIO_PORT               GPIOA
#define D1_POWER_GPIO_CLK                CRM_GPIOA_PERIPH_CLOCK

void init_d1_power_gpio();

// 12v power
#define PD1_12V_POWER_PIN                GPIO_PINS_1
#define PD1_12V_POWER_GPIO_PORT          GPIOD
#define PD1_12V_POWER_GPIO_CLK           CRM_GPIOD_PERIPH_CLOCK

void init_pd1_12v_power_gpio();

// 5v power
#define PD0_5V_POWER_PIN                GPIO_PINS_0
#define PD0_5V_POWER_GPIO_PORT          GPIOD
#define PD0_5V_POWER_GPIO_CLK           CRM_GPIOD_PERIPH_CLOCK

void init_pd0_5v_power_gpio();

// Watch Dog
void init_wdt();
void wdt_reload();

// State
void load_state_from_storage();

void save_rain_state(uint16_t mode);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif


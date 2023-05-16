/*
 * mcu_eeprom.c
 *
 *  Created on: 2023 Feb 24
 *      Author: ruffman
 */
#include <stdio.h>

#include "at32f415_board.h"
#include "i2c_application.h"

extern i2c_handle_type hi2cx;

#define BUF_SIZE                         8
#define I2C_TIMEOUT                      0xFFFFF

uint8_t tx_buf1[BUF_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
uint8_t rx_buf1[BUF_SIZE] = {0};

void update_eeprom_param(){
	i2c_status_type i2c_status;

	printf("Check eeprom params\r\n");
	delay_ms(100);


    /* start the request reception process */
//    if((i2c_status = i2c_master_receive(&hi2cx, C64_ADDRESS, rx_buf1, 3, I2C_TIMEOUT)) != I2C_OK)
//    {
//    	printf("receive failed: %d\r\n", i2c_status);
//    }else{
//    	printf("receive succeed\r\n");
//    }
//
//    delay_ms(100);

    /* start the request reception process */
//    if((i2c_status = i2c_master_transmit(&hi2cx, C64_ADDRESS, tx_buf1, 2, I2C_TIMEOUT)) != I2C_OK)
//    {
//    	printf("transmit failed: %d\r\n", i2c_status);
//    }
//    else{
//    	printf("transmit succeed\r\n");
//    }

    /* write data to memory device */
//    if((i2c_status = i2c_memory_write(&hi2cx, I2C_MEM_ADDR_WIDIH_16, I2C1_ADDRESS, 0x01, tx_buf1, 1, I2C_TIMEOUT)) != I2C_OK)
//    {
//    	printf("write i2c eeprom failed. %d\r\n", i2c_status);
//    }

    /* read data from memory device */
	    if((i2c_status = i2c_memory_read(&hi2cx, I2C_MEM_ADDR_WIDIH_16, C64_ADDRESS, 0x01, tx_buf1, 1, I2C_TIMEOUT)) != I2C_OK)
	    {
	    	printf("write i2c eeprom failed. %d\r\n", i2c_status);
	    }
}

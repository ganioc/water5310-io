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

uint8_t tx_buf1[BUF_SIZE] = { 0x31, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
uint8_t rx_buf1[BUF_SIZE] = { 0 };

void update_eeprom_param() {
	i2c_status_type i2c_status;

	printf("Check eeprom params\r\n");
	delay_ms(100);

	/* write data to memory device */
    if((i2c_status = i2c_memory_write(&hi2cx, I2C_MEM_ADDR_WIDIH_16,
    		EEPROM_ADDRESS, 0x0, tx_buf1, 1, I2C_TIMEOUT)) != I2C_OK)
    {
    	printf("write i2c eeprom failed. %d\r\n", i2c_status);
    }
    delay_ms(100);

	/* read data from memory device */
	if ((i2c_status = i2c_memory_read(&hi2cx, I2C_MEM_ADDR_WIDIH_16,
			EEPROM_ADDRESS, 0x0, rx_buf1, 1, I2C_TIMEOUT)) != I2C_OK) {
		printf("write i2c eeprom failed. %d\r\n", i2c_status);
	}else{
		printf("read 0x00: %02X\n", rx_buf1[0]);
	}
}
int read_EEPROM(uint16_t addr, uint8_t *data, int len){
	i2c_status_type i2c_status;
	/* read data from memory device */
	if ((i2c_status = i2c_memory_read(&hi2cx, I2C_MEM_ADDR_WIDIH_16,
			EEPROM_ADDRESS, addr, data, len, I2C_TIMEOUT)) != I2C_OK) {
		printf("write i2c eeprom failed. %d\r\n", i2c_status);
		return -1;
	}else{
		return 0;
	}
}
int write_EEPROM(uint16_t addr, uint8_t *data, int len){
	i2c_status_type i2c_status;
	/* write data to memory device */
//	delay_ms(10);
	i2c_status = i2c_memory_write(&hi2cx, I2C_MEM_ADDR_WIDIH_16,
	    		EEPROM_ADDRESS, addr, data, len, I2C_TIMEOUT);

	delay_ms(10);

    if(i2c_status != I2C_OK)
    {
    	printf("write i2c eeprom failed. %d\r\n", i2c_status);
    	return -1;
    }else{
    	printf("write i2c eeprom succeed: %d\r\n", data[0]);
    	return 0;
    }
}
int read_EEPROM_DC(uint8_t *data, int len){
	return read_EEPROM(EEPROM_DC_ON, data, len);
}
int read_EEPROM_ADC(uint8_t *data, int len){
	return read_EEPROM(EEPROM_ADC_ON, data, len);
}
int write_EEPROM_DC(uint8_t *data, int len){
	return write_EEPROM(EEPROM_DC_ON, data, len);
}
int write_EEPROM_ADC(uint8_t *data, int len){
	return write_EEPROM(EEPROM_ADC_ON, data, len);
}

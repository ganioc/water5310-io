/*
 * mcu_i2c.c
 *
 *  Created on: 2023 Feb 24
 *      Author: ruffman
 */

#include "at32f415_board.h"
#include "i2c_application.h"

#include <stdio.h>

i2c_handle_type hi2cx;

/**
  * @brief  initializes peripherals used by the i2c.
  * @param  none
  * @retval none
  */
void i2c_lowlevel_init(i2c_handle_type* hi2c)
{
  gpio_init_type gpio_initstructure;

  if(hi2c->i2cx == I2C1_PORT)
  {
	printf("init i2c1\r\n");

    /* i2c periph clock enable */
    crm_periph_clock_enable(I2C1_CLK, TRUE);
    crm_periph_clock_enable(I2C1_SCL_GPIO_CLK, TRUE);
    crm_periph_clock_enable(I2C1_SDA_GPIO_CLK, TRUE);


    // enable iomux clock,
    crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);

    // remap i2c2 pf6/pf7,
    gpio_pin_remap_config(I2C1_GMUX_0010,TRUE);

    /* gpio configuration */
    gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_OPEN_DRAIN;
    gpio_initstructure.gpio_pull           = GPIO_PULL_UP;
    gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
    gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;

    /* configure i2c pins: scl */
    gpio_initstructure.gpio_pins = I2C1_SCL_PIN;
    gpio_init(I2C1_SCL_GPIO_PORT, &gpio_initstructure);
    // This is for ATF421
    // gpio_pin_mux_config(I2C1_SCL_GPIO_PORT, I2C1_SCL_PIN, GPIO_MUX_2);
    // gpio_pin_remap_config(I2C2_GMUX_0010,TRUE);

    /* configure i2c pins: sda */
    gpio_initstructure.gpio_pins = I2C1_SDA_PIN;
    gpio_init(I2C1_SDA_GPIO_PORT, &gpio_initstructure);

    // gpio_pin_remap_config(I2C2_GMUX_0010,TRUE);



    /* configure and enable i2c dma channel interrupt */
//    nvic_irq_enable(I2Cx_DMA_TX_IRQn, 0, 0);
//    nvic_irq_enable(I2Cx_DMA_RX_IRQn, 0, 0);

    /* configure and enable i2c interrupt */
//    nvic_irq_enable(I2Cx_EVT_IRQn, 0, 0);
//    nvic_irq_enable(I2Cx_ERR_IRQn, 0, 0);

//    /* i2c dma tx and rx channels configuration */
//    /* enable the dma clock */
//    crm_periph_clock_enable(I2Cx_DMA_CLK, TRUE);
//
//    /* i2c dma channel configuration */
//    dma_reset(hi2c->dma_tx_channel);
//    dma_reset(hi2c->dma_rx_channel);
//
//    hi2c->dma_tx_channel = I2Cx_DMA_TX_CHANNEL;
//    hi2c->dma_rx_channel = I2Cx_DMA_RX_CHANNEL;
//
//    dma_default_para_init(&hi2c->dma_init_struct);
//    hi2c->dma_init_struct.peripheral_inc_enable    = FALSE;
//    hi2c->dma_init_struct.memory_inc_enable        = TRUE;
//    hi2c->dma_init_struct.peripheral_data_width    = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
//    hi2c->dma_init_struct.memory_data_width        = DMA_MEMORY_DATA_WIDTH_BYTE;
//    hi2c->dma_init_struct.loop_mode_enable         = FALSE;
//    hi2c->dma_init_struct.priority                 = DMA_PRIORITY_LOW;
//    hi2c->dma_init_struct.direction                = DMA_DIR_MEMORY_TO_PERIPHERAL;
//
//    dma_init(hi2c->dma_tx_channel, &hi2c->dma_init_struct);
//    dma_init(hi2c->dma_rx_channel, &hi2c->dma_init_struct);

    i2c_init(hi2c->i2cx, I2C_FSMODE_DUTY_2_1, I2C1_SPEED);

    i2c_own_address1_set(hi2c->i2cx, I2C_ADDRESS_MODE_7BIT, I2C1_ADDRESS);
  }
}

void init_i2c_2(){
	hi2cx.i2cx = I2C1_PORT;

	i2c_config(&hi2cx);

}

//#define I2Cx_DMA_TX_IRQHandler           DMA1_Channel4_IRQHandler
//#define I2Cx_DMA_RX_IRQHandler           DMA1_Channel5_IRQHandler
//#define I2Cx_EVT_IRQHandler              I2C2_EVT_IRQHandler
//#define I2Cx_ERR_IRQHandler              I2C2_ERR_IRQHandler

/**
  * @brief  this function handles dma interrupt request.
  * @param  none
  * @retval none
  */
//void I2Cx_DMA_RX_IRQHandler(void)
//{
//  i2c_dma_rx_irq_handler(&hi2cx);
//}

/**
  * @brief  this function handles dma interrupt request.
  * @param  none
  * @retval none
  */
//void I2Cx_DMA_TX_IRQHandler(void)
//{
//  i2c_dma_tx_irq_handler(&hi2cx);
//}

/**
  * @brief  this function handles i2c event interrupt request.
  * @param  none
  * @retval none
  */
//void I2Cx_EVT_IRQHandler(void)
//{
//  i2c_evt_irq_handler(&hi2cx);
//}

/**
  * @brief  this function handles i2c error interrupt request.
  * @param  none
  * @retval none
  */
//void I2Cx_ERR_IRQHandler(void)
//{
//  i2c_err_irq_handler(&hi2cx);
//}

/**
  * @}
  */

/**
  * @}
  */


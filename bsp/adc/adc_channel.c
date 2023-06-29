/*
 * adc_channel.c
 *
 *  Created on: 2023 Feb 22
 *      Author: ruffman
 */
#include "at32f415_board.h"

#define ADC_REPEAT_TIMES    100

#define ADC_MEASURE_NUM     10

#define CHANNEL_IOVOL       9
#define CHANNEL_VERF        0

struct ADC_CHAN chan_list[ADC_MEASURE_NUM] = { { id:0, mode:VOLTAGE }, { id:1,
		mode:VOLTAGE }, { id:2, mode:VOLTAGE }, { id:3, mode:VOLTAGE }, { id:4,
		mode:VOLTAGE }, { id:5, mode:VOLTAGE }, { id:6, mode:VOLTAGE }, { id:7,
		mode:VOLTAGE }, { id:8, mode:VOLTAGE }, { id:9, mode:VOLTAGE }, };
__IO uint16_t adc1_ordinary_value[ADC_MEASURE_NUM] = { 0 };
uint16_t adc1_repeated_values[ADC_REPEAT_TIMES][ADC_MEASURE_NUM] = { 0 };

void adc_mode_set(uint8_t channel, uint8_t mode) {
	if (mode) {
		chan_list[channel - 1].mode = CURRENT;
	} else {
		chan_list[channel - 1].mode = VOLTAGE;
	}
}
uint8_t adc_mode_get(uint8_t channel) {
	if (chan_list[channel - 1].mode == VOLTAGE) {
		return 0;
	} else {
		return 1;
	}
}

static void dma_config() {
	dma_init_type dma_init_struct;

	crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);
	dma_reset(DMA1_CHANNEL1);

	dma_default_para_init(&dma_init_struct);
	dma_init_struct.buffer_size = ADC_MEASURE_NUM;
	dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
	dma_init_struct.memory_base_addr = (uint32_t) adc1_ordinary_value;
	dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_HALFWORD;
	dma_init_struct.memory_inc_enable = TRUE;

	dma_init_struct.peripheral_base_addr = (uint32_t) &(ADC1->odt);
	dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_HALFWORD;
	dma_init_struct.peripheral_inc_enable = FALSE;
	dma_init_struct.priority = DMA_PRIORITY_HIGH;
	dma_init_struct.loop_mode_enable = TRUE;

	dma_init(DMA1_CHANNEL1, &dma_init_struct);
	dma_channel_enable(DMA1_CHANNEL1, TRUE);
}

static void adc_config(void) {
	adc_base_config_type adc_base_struct;
	crm_periph_clock_enable(CRM_ADC1_PERIPH_CLOCK, TRUE);
	crm_adc_clock_div_set(CRM_ADC_DIV_6);

	adc_base_default_para_init(&adc_base_struct);
	adc_base_struct.sequence_mode = TRUE;
	adc_base_struct.repeat_mode = FALSE;
	adc_base_struct.data_align = ADC_RIGHT_ALIGNMENT;
	adc_base_struct.ordinary_channel_length = ADC_MEASURE_NUM;
	adc_base_config(ADC1, &adc_base_struct);

	adc_ordinary_channel_set(ADC1, ADC_CHANNEL_17, 1, ADC_SAMPLETIME_239_5);
	adc_ordinary_channel_set(ADC1, ADC_CHANNEL_0, 2, ADC_SAMPLETIME_239_5);
	adc_ordinary_channel_set(ADC1, ADC_CHANNEL_1, 3, ADC_SAMPLETIME_239_5);
	adc_ordinary_channel_set(ADC1, ADC_CHANNEL_2, 4, ADC_SAMPLETIME_239_5);
	adc_ordinary_channel_set(ADC1, ADC_CHANNEL_3, 5, ADC_SAMPLETIME_239_5);
	adc_ordinary_channel_set(ADC1, ADC_CHANNEL_4, 6, ADC_SAMPLETIME_239_5);
	adc_ordinary_channel_set(ADC1, ADC_CHANNEL_5, 7, ADC_SAMPLETIME_239_5);
	adc_ordinary_channel_set(ADC1, ADC_CHANNEL_6, 8, ADC_SAMPLETIME_239_5);
	adc_ordinary_channel_set(ADC1, ADC_CHANNEL_7, 9, ADC_SAMPLETIME_239_5);
	adc_ordinary_channel_set(ADC1, ADC_CHANNEL_8, 10, ADC_SAMPLETIME_239_5);

	adc_ordinary_conversion_trigger_set(
	ADC1, ADC12_ORDINARY_TRIG_SOFTWARE, TRUE);
	adc_dma_mode_enable(ADC1, TRUE);
	adc_tempersensor_vintrv_enable(TRUE);

	adc_enable(ADC1, TRUE);

	adc_calibration_init(ADC1);
	while (adc_calibration_init_status_get(ADC1))
		;
	adc_calibration_start(ADC1);
	while (adc_calibration_status_get(ADC1))
		;
}

void init_adc() {
	// gpio set to analog mode
	gpio_init_type gpio_initstructure;
	crm_periph_clock_enable(ADC_CHAN_CRM_CLOCK, TRUE);

	gpio_default_para_init(&gpio_initstructure);
	gpio_initstructure.gpio_mode = GPIO_MODE_ANALOG;
	gpio_initstructure.gpio_pins =
	ADC_CHAN_0_PIN |
	ADC_CHAN_1_PIN |
	ADC_CHAN_2_PIN |
	ADC_CHAN_3_PIN |
	ADC_CHAN_4_PIN |
	ADC_CHAN_5_PIN |
	ADC_CHAN_6_PIN |
	ADC_CHAN_7_PIN;

	gpio_init(ADC_CHAN_PORT, &gpio_initstructure);

	// channel 8, PB0,
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	gpio_default_para_init(&gpio_initstructure);
	gpio_initstructure.gpio_mode = GPIO_MODE_ANALOG;
	gpio_initstructure.gpio_pins = ADC_INVOL_PIN;
	gpio_init(ADC_INVOL_PORT, &gpio_initstructure);

	dma_config();
	adc_config();

}
static void adc_repeat_read() {

	for (int i = 0; i < ADC_REPEAT_TIMES; i++) {

		adc_ordinary_software_trigger_enable(ADC1, TRUE);

		while (dma_flag_get(DMA1_FDT1_FLAG) == RESET)
			;

		dma_flag_clear(DMA1_FDT1_FLAG);

		for (int j = 0; j < ADC_MEASURE_NUM; j++) {
			adc1_repeated_values[i][j] = adc1_ordinary_value[j];
		}
	}

	for (int i = 0; i < ADC_MEASURE_NUM; i++) {
		uint32_t sum = 0;
		for (int j = 0; j < ADC_REPEAT_TIMES; j++) {
			sum += adc1_repeated_values[j][i];
		}
		adc1_ordinary_value[i] = (uint16_t )(sum / ADC_REPEAT_TIMES);
	}
}
/*
 * Return channel raw voltage value and computed vref value,
 */
void adc_get(uint8_t channel, uint16_t *v_ref, uint16_t *val) {
	float vref;

	adc_repeat_read();

	printf("ordinary_value:%d\r\n", adc1_ordinary_value[0]);

	for (int i = 0; i < ADC_MEASURE_NUM; i++) {
		printf("%d %d\r\n", i, adc1_ordinary_value[i]);
	}

	vref = ((float) 1.2 * 4095) / adc1_ordinary_value[0];
	printf("vref_value = %0.3f V\r\n", vref);

	*v_ref = adc1_ordinary_value[0];
	*val = adc1_ordinary_value[channel];
}



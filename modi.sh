#!/bin/bash

echo -e "Change flash map area"

sed -i  '/FLASH (rx)      : ORIGIN = /c\FLASH (rx)      : ORIGIN = 0x08008000, LENGTH = 224K' ldscripts/AT32F415xC_FLASH.ld

sed -i  '/.*\/\/ nvic_vector_table/c\  nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x8000);' user/main.c

echo -e "Done"
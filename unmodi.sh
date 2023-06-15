#!/bin/bash

echo -e "change flash map back"

sed -i  '/FLASH (rx)      : ORIGIN = /c\FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 256K' ldscripts/AT32F415xC_FLASH.ld
sed -i  '/.*nvic_vector_table/c\  // nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x8000);' user/main.c

echo -e "Done"
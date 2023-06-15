#!/bin/bash

echo -e "Change flash map area"

FILENAME=$1

if [ ! -n "${FILENAME}" ]; then
	echo "Exit"
	echo "Error: Please input filename"
	exit 1
else 
	echo "map file: ${FILENAME}" 
fi

sed -i  '/FLASH (rx)      : ORIGIN = /c\FLASH (rx)      : ORIGIN = 0x08008000, LENGTH = 224K' ${FILENAME}
sed -i  '/.*\/\/ nvic_vector_table/c\  nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x8000);' ${FILENAME}
echo -e "Done"


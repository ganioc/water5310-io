#!/bin/bash

echo -e "change flash map back"

FILENAME=$1

if [ ! -n "${FILENAME}" ]; then
        echo "Exit"
        echo "Error: Please input filename"
        exit 1
else
        echo "unmap file: ${FILENAME}"
fi

sed -i  '/FLASH (rx)      : ORIGIN = /c\FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 256K' ${FILENAME}
sed -i  '/.*nvic_vector_table/c\  // nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x8000);' ${FILENAME}

echo -e "Done"


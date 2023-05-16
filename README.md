## Fmo415 雨量计的MCU程序


### EEPROM的使用
之前I2C的读取一直有问题，原因是AT32IDE自带的SDK的I2C代码有问题，导致I2C发送错误。所以采用了AT32内置的Flash模拟EEPROM的方式来保存参数。

EEPROM的最大写次数比FLASH高一个数量级。所以增加I2C-EEPROM读写参数的接口。




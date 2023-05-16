## Fmo415 雨量计的MCU程序

### LED2
PA12管脚, LED4不亮?LED的控制是反向的。


### EEPROM的使用
之前I2C的读取一直有问题，原因是AT32IDE自带的SDK的I2C代码有问题，导致I2C发送错误。所以采用了AT32内置的Flash模拟EEPROM的方式来保存参数。

EEPROM的最大写次数比FLASH高一个数量级。所以增加I2C-EEPROM读写参数的接口。

### EEPROM的参数
ADDR: A0,A1,都为0, 0xA0, 16-bit address, 8 bit read out, 

Model: FT24C1024A,
`
I2C1, U7, 

Library: 从BSP library里面拷贝i2c_application.h|c 文件,




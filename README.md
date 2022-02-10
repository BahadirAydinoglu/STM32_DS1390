# DS1390-STM32
DS1390 is a one of the Real Time Clock IC. It works with SPI protocols. 
Driver is has written with software SPI protocols which used HAL library, not hardware.
CubeMx configuration files is added.
SPI Pins must be defined as below

#define SPI_CS_Pin 
#define SPI_CS_GPIO_Port
#define SPI_MISO_Pin 
#define SPI_MISO_GPIO_Port 
#define SPI_MOSI_Pin 
#define SPI_MOSI_GPIO_Port 
#define SPI_SCLK_Pin 
#define SPI_SCLK_GPIO_Port 

It tested with STM32F072RB-Nucloe boards.

Hava a fun !
Bahadır AYDINOĞLU  @2022

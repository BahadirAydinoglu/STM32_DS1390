#ifndef	__DS1390_H_
#define	__DS1390_H_
#include "stdint.h"

#define CSLow()		  HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET)
#define	CSHigh()	  HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET)
#define	MOSILow()	  HAL_GPIO_WritePin(SPI_MOSI_GPIO_Port, SPI_MOSI_Pin, GPIO_PIN_RESET)
#define	MOSIHigh()	HAL_GPIO_WritePin(SPI_MOSI_GPIO_Port, SPI_MOSI_Pin, GPIO_PIN_SET)
#define	CLKLow()	  HAL_GPIO_WritePin(SPI_SCLK_GPIO_Port, SPI_SCLK_Pin, GPIO_PIN_RESET)
#define CLKHigh()	  HAL_GPIO_WritePin(SPI_SCLK_GPIO_Port, SPI_SCLK_Pin, GPIO_PIN_SET)
#define	MISOState()	HAL_GPIO_ReadPin(SPI_MISO_GPIO_Port,SPI_MISO_Pin)

void write_ds1390_byte(int cmd);
void write_ds1390(int cmd, int data);
int read_ds1390(int cmd);
void rtc_init_hw(void);
void rtc_init(void);
void rtc_set_datetime(	int day,	int mth,	int year, int dow,
						int hr,		int min,	int sec);
void rtc_get_date(	int *day,	int *mth,
					int *year,	int *dow);
void rtc_get_time(int *hr, int *min, int *sec);
void WriteSpiCmd(int cmd,int data);
int ReadSpiCmd(int cmd);
void delay(void);
int BCD2DEC(int c);
int DEC2BCD(int c);
#endif	//__DS1390_H_

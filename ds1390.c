#include "main.h"
#include "gpio.h"
#include "ds1390.h"


#define	_NO_CHARGE			    0b00000000
#define	_NO_DIODE_250R_RES	0b10100101
#define	_ONE_DIODE_250R_RES	0b10101001
#define	_NO_DIODE_2K_RES	  0b10100110
#define	_ONE_DIODE_2K_RES	  0b10101010
#define	_NO_DIODE_4K_RES	  0b10100111
#define	_ONE_DIODE_4K_RES	  0b10101011

void delay(void)
{
  __NOP();__NOP();__NOP();__NOP();__NOP(); 
}

void WriteSpiCmd(int cmd,int data)
{
	int DataState=0;
	CSLow();
	delay();
	CLKLow();	
	delay();	
	for(int i=0;i<8;i++)
	{
		DataState=(cmd & 0x80);
		CLKHigh();			
    if(DataState)
			MOSIHigh();
		else
			MOSILow();	
    delay();    
		CLKLow();		
		delay();
		cmd=cmd<<1;
	}	
	for(int i=0;i<8;i++)
	{
		DataState=(data & 0x80);
		CLKHigh();			
    if(DataState)
			MOSIHigh();
		else
			MOSILow();	
    delay();    
		CLKLow();		
		delay();
		data=data<<1;
	}	
	CSHigh();		
  delay();
  CLKLow();	
}
	
int ReadSpiCmd(int cmd)
{
	unsigned int DataState=0,DataInCome=0;
	CSLow();
	delay();
	CLKLow();	
	delay();
	for(int i=0;i<8;i++)
	{
		DataState=(cmd & 0x80);
		CLKHigh();			
    if(DataState)
			MOSIHigh();
		else
			MOSILow();	
    delay();    
		CLKLow();		
		delay();
		cmd=cmd<<1;
	} 
  delay();
	for(int i=0;i<8;i++)
	{
    DataInCome=DataInCome<<1;
		CLKHigh();	
		delay();
		CLKLow();				
		delay();
		if(MISOState())
			DataInCome++;				
	}	
	CSHigh();
  delay();
	CLKLow();
	//DataInCome=DataInCome & 0x7F;
	return	((int)DataInCome);
}
void rtc_init(void)
{
  CSLow();
  __NOP();
  CSHigh();	
  delay();
	CLKLow();	
	WriteSpiCmd(0x8D, 0x00);
  delay();
	WriteSpiCmd(0x8F, 0x00);
	int	temp = ReadSpiCmd(0x03);
	
  
	if((temp & 0x0040) > 0)
		WriteSpiCmd(0x83,(temp & 0x001F));		// Hour Reg
  
}
void rtc_set_datetime(	int day,	int mth,	int year, int dow,
						int hr,		int min,	int sec)
{  

  day = DEC2BCD(day);
  mth = DEC2BCD(mth);
  year = DEC2BCD(year);
  dow = DEC2BCD(dow);
  hr = DEC2BCD(hr);
  min = DEC2BCD(min);
  sec = DEC2BCD(sec);
  
  
  WriteSpiCmd(0x81,sec);
  delay();
  WriteSpiCmd(0x82,min);
  delay();
  WriteSpiCmd(0x83,hr);
  delay();
  WriteSpiCmd(0x84,dow);
  delay();  
	WriteSpiCmd(0x85,day);
  delay();
	WriteSpiCmd(0x86,mth);
  delay();
	WriteSpiCmd(0x87,year);	
  delay();
	
	
}
void rtc_get_date(	int *day,	int *mth,
					int *year,	int *dow)
{
  int temp;
	temp = ReadSpiCmd(0x05);
  temp = (temp & 0x0F) + ((temp>>4)*10);
	if( (1<=temp) && (temp<=31))
		*day	= temp;  

	temp = ReadSpiCmd(0x06);
  temp &= 0x1F;
  temp = (temp & 0x0F) + ((temp>>4)*10);
	if( (1<=temp) && (temp<=12))
		*mth	= temp;  

	temp = ReadSpiCmd(0x07);
  temp = (temp & 0x0F) + ((temp>>4)*10);
	if( (0<=temp) && (temp<=99))
		*year	= temp;  

	temp = ReadSpiCmd(0x04);
  temp = (temp & 0x0F) + ((temp>>4)*10);
	if( (1<=temp) && (temp<=7))
		*dow	= temp;
}
//............................................... rtc_get_time
void rtc_get_time(int *hr, int *min, int *sec)
{
    int temp=0;  
    temp = ReadSpiCmd(0x01);
    temp = (temp & 0x0F) + ((temp>>4)*10);
//  temp = BCD2DEC(temp);
//	if( (0<=temp) && (temp<=59))
		*sec	= temp;  
  
  
    temp = ReadSpiCmd(0x02);
    temp = (temp & 0x0F) + ((temp>>4)*10);
//  temp = BCD2DEC(temp);
//	if( (0<=temp) && (temp<=59))
  
		*min	= temp;
 

    temp = ReadSpiCmd(0x03);
    temp &= 0x3F;
    temp = (temp & 0x0F) + ((temp>>4)*10);
 // temp = BCD2DEC(temp);
//	if( (0<=temp) && (temp<=23))
		*hr	= temp;

	
}
int BCD2DEC(int c) {
    int ch = ((c >> 4) * 10 + (0x0F & c));
    return ch;
}

int DEC2BCD(int c) {
    int ch = ((c / 10) << 4) | (c % 10);
    return ch;
}

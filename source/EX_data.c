/*
 * EX_data.c
 *
 *  Created on: 2018年6月21日
 *      Author: hgisw
 */

#define EX_DATA_C_

#include "EX_data.h"

//00 	 当前功率
//01  	供电电压
//02  	供电电流
//03	 线盘电流
//04  	最大电流
//05  	线盘温度
//06  	锅内温度
//07 	IGBT频率
//08   IGBT温度
//09  	使用容量
//10  	机器状态  32767
//11 	RS232通信故障
//#define MENU1_MAX 12
//static int16 menu1_data[MENU1_MAX]={0,0,0,0,0,0,0,0,0,0,0,0};//串口通信仓库
//00  		 输入密码
//01		最大功率
//02		最大供电电压
//03		最小供电电压
//04		最大线盘电流
//05		最大线盘温度
//06		通用线盘温度
//07		最大锅内温度
//08		最大漏料温度
//09		最大IGBT频率
//10		最小IGBT频率
//11		最大IGBT温度
//12		限制工作时间
//13        恢复出厂设置
#define MENU2_MAX 11
static int16 menu2_data[MENU2_MAX]={
		111,2,3,4,5,6,7,8,9,121,-22};//串口通信仓库
const int16 default_value[MENU2_MAX]={
	8888,//		== 50  		 输入密码
	300,//		== 51		最大功率
	1500,//		== 52		最大线盘电流
	1300,//		== 53		最大线盘温度
	8000,//		== 54		最大锅内温度
	1000,//		== 55		最大漏料温度
	200,//		== 56		最大IGBT频率
	50,//		== 57		最小IGBT频率
	700,//		== 58		最大IGBT温度
	0,//		== 59		限制工作时间
	0,//		== 60                       恢复出厂设置密码 1524
};

static bool password = false;//

void CompareMenu1Data(Uint8 index)
{
	switch(index)
	{
	case 0:
		Usart_Cmd_Send(index,StartTranslateAdc(0));
		break;
	default:
		Usart_Cmd_Send(index,StartTranslateAdc(0));
		break;
	}

}
void SendMenu2Data(Uint8 index)
{
	switch(index)
	{
		case 0:	Usart_Cmd_Send(50,0);
			break;
		case 10: Usart_Cmd_Send(50+index,0);
			break;
		default:	Usart_Cmd_Send(50+index,menu2_data[index]);
			break;
	}
}
void CompareMenu2Data(Uint8 index,int16 value)
{
	switch(index)
	{
	case 0:	value = clamp(value,0,32767); //		== 50  		 输入密码
		if(!password && menu2_data[0] == value)
		{
			password = true;
			Usart_Cmd_Send(50,menu2_data[0]);//密码正确就显示正确的密码，如果不正确就显示0，修改失败
		}
		else if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
			Usart_Cmd_Send(50,menu2_data[index]);
		}
		else
		{
			Usart_Cmd_Send(50,0);
		}
		break;
	case 1:	value = clamp(value,0,300); //			== 51		最大功率
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 2:	value = clamp(value,0,3000); //			== 52		最大线盘电流
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 3: value= clamp(value,0,3000); //53		最大线盘温度
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 4: value = clamp(value,0,12000); //54		最大锅内温度
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 5: value = clamp(value,0,3000);//55		最大漏料温度
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 6: value= clamp(value,10,1000);//56		最大IGBT频率
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 7: value = clamp(value,10,1000);//57		最小IGBT频率
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 8 : value = clamp(value,550,750);//58		最大IGBT温度
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 9: value = clamp(value,0,10000);//59		限制工作时间
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 10: value = clamp(value,0,32767);//60                       恢复出厂设置
		if(value == INIT_PASSWORD)
		{
			SetDefaulLocationtData();
			InitLocationData();
			password = false;
			Usart_Cmd_Send(50+index,INIT_PASSWORD);
		}
		else
		{
			Usart_Cmd_Send(50+index,0);
		}
		break;
	}
}
void InitLocationData()
{
	Uint8 i =0;
	for(i=0;i<MENU2_MAX;i++)
	{
		menu2_data[i] =Read_Data_EEPROM(i);
	}
}
void SetDefaulLocationtData()
{
	Uint8 i =0;
	for(i=0;i<MENU2_MAX;i++)
	{
		//menu2_data[i] =default_value[i];
		Write_Data_EERPOM(i,default_value[i]);
	}
}
void Write_Data_EERPOM(Uint8 index,int16 value)
{
	Spi_Write(value>>8,index*2);
	Spi_Write(value,index*2+1);
}
int16 Read_Data_EEPROM(Uint8 index)
{
	int16 dat = 0;
	dat =Spi_Read(index*2);
	dat=dat<<8;
	dat |=Spi_Read(index*2+1);
	return dat;
}

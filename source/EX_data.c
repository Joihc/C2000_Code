/*
 * EX_data.c
 *
 *  Created on: 2018��6��21��
 *      Author: hgisw
 */

#define EX_DATA_C_

#include "EX_data.h"

//00 	 ��ǰ����
//01  	�����ѹ
//02  	�������
//03	 ���̵���
//04  	������
//05  	�����¶�
//06  	�����¶�
//07 	IGBTƵ��
//08   IGBT�¶�
//09  	ʹ������
//10  	����״̬  32767
//11 	RS232ͨ�Ź���
//#define MENU1_MAX 12
//static int16 menu1_data[MENU1_MAX]={0,0,0,0,0,0,0,0,0,0,0,0};//����ͨ�Ųֿ�
//00  		 ��������
//01		�����
//02		��󹩵��ѹ
//03		��С�����ѹ
//04		������̵���
//05		��������¶�
//06		ͨ�������¶�
//07		�������¶�
//08		���©���¶�
//09		���IGBTƵ��
//10		��СIGBTƵ��
//11		���IGBT�¶�
//12		���ƹ���ʱ��
//13        �ָ���������
#define MENU2_MAX 11
static int16 menu2_data[MENU2_MAX]={
		111,2,3,4,5,6,7,8,9,121,-22};//����ͨ�Ųֿ�
const int16 default_value[MENU2_MAX]={
	8888,//		== 50  		 ��������
	300,//		== 51		�����
	1500,//		== 52		������̵���
	1300,//		== 53		��������¶�
	8000,//		== 54		�������¶�
	1000,//		== 55		���©���¶�
	200,//		== 56		���IGBTƵ��
	50,//		== 57		��СIGBTƵ��
	700,//		== 58		���IGBT�¶�
	0,//		== 59		���ƹ���ʱ��
	0,//		== 60                       �ָ������������� 1524
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
	case 0:	value = clamp(value,0,32767); //		== 50  		 ��������
		if(!password && menu2_data[0] == value)
		{
			password = true;
			Usart_Cmd_Send(50,menu2_data[0]);//������ȷ����ʾ��ȷ�����룬�������ȷ����ʾ0���޸�ʧ��
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
	case 1:	value = clamp(value,0,300); //			== 51		�����
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 2:	value = clamp(value,0,3000); //			== 52		������̵���
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 3: value= clamp(value,0,3000); //53		��������¶�
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 4: value = clamp(value,0,12000); //54		�������¶�
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 5: value = clamp(value,0,3000);//55		���©���¶�
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 6: value= clamp(value,10,1000);//56		���IGBTƵ��
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 7: value = clamp(value,10,1000);//57		��СIGBTƵ��
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 8 : value = clamp(value,550,750);//58		���IGBT�¶�
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 9: value = clamp(value,0,10000);//59		���ƹ���ʱ��
		if(password && menu2_data[index] != value)
		{
			Write_Data_EERPOM(index,value);
			menu2_data[index] = Read_Data_EEPROM(index);
		}
		Usart_Cmd_Send(50+index,menu2_data[index]);
		break;
	case 10: value = clamp(value,0,32767);//60                       �ָ���������
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

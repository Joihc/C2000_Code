/*
 * EX_i2c.c
 *
 *  Created on: 2018��6��19��
 *      Author: hgisw
 */
#define EX_I2C_C_

#include "EX_i2c.h"



void Set_SDA(unsigned char dat)
{
	EALLOW;
	GpioMuxRegs.GPFDIR.bit.GPIOF2 = 1;
	EDIS;
	GpioDataRegs.GPFDAT.bit.GPIOF2 =(dat?1:0);
}
void Set_SCL(unsigned char dat)
{
	EALLOW;
	GpioMuxRegs.GPFDIR.bit.GPIOF3 = 1;
	EDIS;
	GpioDataRegs.GPFDAT.bit.GPIOF3 =(dat?1:0);
}
unsigned char Read_SDA()
{
	EALLOW;
	GpioMuxRegs.GPFDIR.bit.GPIOF2 = 0;
	EDIS;
	return GpioDataRegs.GPFDAT.bit.GPIOF2;

}
unsigned char Read_SCL()
{
	EALLOW;
	GpioMuxRegs.GPFDIR.bit.GPIOF3 = 0;
	EDIS;
	return GpioDataRegs.GPFDAT.bit.GPIOF3;
}
/*******************************************************************************
* ������         : I2cStart()
* ��������		 : ��ʼ�źţ���SCLʱ���ź��ڸߵ�ƽ�ڼ�Read_SDA()�źŲ���һ���½���
* ����           : ��
* ���         	 : ��
* ��ע           : ��ʼ֮��Read_SDA()��SCL��Ϊ0
*******************************************************************************/

void I2cStart()
{
	Set_SDA(1);
	DELAY_US(5);
	Set_SCL(1);
	DELAY_US(5);//����ʱ����Read_SDA()����ʱ��>4.7us
	Set_SDA(0);
	DELAY_US(5);//����ʱ����>4us
	Set_SCL(0);
	DELAY_US(5);
}
/*******************************************************************************
* ������         : I2cStop()
* ��������		 : ��ֹ�źţ���SCLʱ���źŸߵ�ƽ�ڼ�Read_SDA()�źŲ���һ��������
* ����           : ��
* ���         	 : ��
* ��ע           : ����֮�󱣳�Read_SDA()��SCL��Ϊ1����ʾ���߿���
*******************************************************************************/

void I2cStop()
{
	Set_SDA(0);
	DELAY_US(5);
	Set_SCL(1);
	DELAY_US(5);//����ʱ�����4.7us
	Set_SDA(1);
	DELAY_US(5);
}
/*******************************************************************************
* ������         : I2cSendByte(unsigned char dat)
* ��������		 : ͨ��I2C����һ���ֽڡ���SCLʱ���źŸߵ�ƽ�ڼ䣬���ַ����ź�Read_SDA()�����ȶ�
* ����           : num
* ���         	 : 0��1�����ͳɹ�����1������ʧ�ܷ���0
* ��ע           : ������һ���ֽ�Set_SCL(0),Set_Read_SDA()(1)
*******************************************************************************/

unsigned char I2cSendByte(unsigned char dat)
{
	unsigned char a=0,b=0;//���255��һ����������Ϊ1us�������ʱ255us��
	for(a=0;a<8;a++)//Ҫ����8λ�������λ��ʼ
	{
		Set_SDA(dat&(0x80>>a));//Set_SDA(dat>>7);	 //��ʼ�ź�֮��Set_SCL(0)�����Կ���ֱ�Ӹı�Read_SDA()�ź�
		//dat=dat<<1;
		DELAY_US(5);
		Set_SCL(1);
		DELAY_US(5);//����ʱ��>4.7us
		Set_SCL(0);
		DELAY_US(5);//ʱ�����4us
	}
	Set_SDA(1);
	DELAY_US(5);
	Set_SCL(1);
	while(Read_SDA())//�ȴ�Ӧ��Ҳ���ǵȴ����豸��Read_SDA()����
	{
		b++;
		if(b>2000)	 //�������2000usû��Ӧ����ʧ�ܣ�����Ϊ��Ӧ�𣬱�ʾ���ս���
		{
			Set_SCL(0);
			DELAY_US(5);
			return 0;
		}
	}
	Set_SCL(0);
	DELAY_US(5);
 	return 1;
}
/*******************************************************************************
* ������         : I2cReadByte()
* ��������		   : ʹ��I2c��ȡһ���ֽ�
* ����           : ��
* ���         	 : dat
* ��ע           : ������һ���ֽ�Set_SCL(0),Set_Read_SDA()(1).
*******************************************************************************/

unsigned char I2cReadByte()
{
	unsigned char a=0,dat=0;
	Set_SDA(1);			//��ʼ�ͷ���һ���ֽ�֮��SCL����0
	DELAY_US(5);
	for(a=0;a<8;a++)//����8���ֽ�
	{
		Set_SCL(1);
		DELAY_US(5);
		dat<<=1;
		dat|=Read_SDA();
		DELAY_US(5);
		Set_SCL(0);
		DELAY_US(5);
	}
	return dat;
}


/*******************************************************************************
* ������         : void At24c02Write(unsigned char addr,unsigned char dat)
* ��������		   : ��24c02��һ����ַд��һ������
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void At24c02Write(unsigned char addr,unsigned char dat)
{
	I2cStart();
	I2cSendByte(0xa0);//����д������ַ
	I2cSendByte(addr);//����Ҫд���ڴ��ַ
	I2cSendByte(dat);	//��������
	I2cStop();
}
/*******************************************************************************
* ������         : unsigned char At24c02Read(unsigned char addr)
* ��������		   : ��ȡ24c02��һ����ַ��һ������
* ����           : ��
* ���         	 : ��
*******************************************************************************/

unsigned char At24c02Read(unsigned char addr)
{
	unsigned char num;
	I2cStart();
	I2cSendByte(0xa0); //����д������ַ
	I2cSendByte(addr); //����Ҫ��ȡ�ĵ�ַ
	I2cStart();
	I2cSendByte(0xa1); //���Ͷ�������ַ
	num=I2cReadByte(); //��ȡ����
	I2cStop();
	return num;
}


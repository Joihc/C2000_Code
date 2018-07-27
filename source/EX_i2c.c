/*
 * EX_i2c.c
 *
 *  Created on: 2018年6月19日
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
* 函数名         : I2cStart()
* 函数功能		 : 起始信号：在SCL时钟信号在高电平期间Read_SDA()信号产生一个下降沿
* 输入           : 无
* 输出         	 : 无
* 备注           : 起始之后Read_SDA()和SCL都为0
*******************************************************************************/

void I2cStart()
{
	Set_SDA(1);
	DELAY_US(5);
	Set_SCL(1);
	DELAY_US(5);//建立时间是Read_SDA()保持时间>4.7us
	Set_SDA(0);
	DELAY_US(5);//保持时间是>4us
	Set_SCL(0);
	DELAY_US(5);
}
/*******************************************************************************
* 函数名         : I2cStop()
* 函数功能		 : 终止信号：在SCL时钟信号高电平期间Read_SDA()信号产生一个上升沿
* 输入           : 无
* 输出         	 : 无
* 备注           : 结束之后保持Read_SDA()和SCL都为1；表示总线空闲
*******************************************************************************/

void I2cStop()
{
	Set_SDA(0);
	DELAY_US(5);
	Set_SCL(1);
	DELAY_US(5);//建立时间大于4.7us
	Set_SDA(1);
	DELAY_US(5);
}
/*******************************************************************************
* 函数名         : I2cSendByte(unsigned char dat)
* 函数功能		 : 通过I2C发送一个字节。在SCL时钟信号高电平期间，保持发送信号Read_SDA()保持稳定
* 输入           : num
* 输出         	 : 0或1。发送成功返回1，发送失败返回0
* 备注           : 发送完一个字节Set_SCL(0),Set_Read_SDA()(1)
*******************************************************************************/

unsigned char I2cSendByte(unsigned char dat)
{
	unsigned char a=0,b=0;//最大255，一个机器周期为1us，最大延时255us。
	for(a=0;a<8;a++)//要发送8位，从最高位开始
	{
		Set_SDA(dat&(0x80>>a));//Set_SDA(dat>>7);	 //起始信号之后Set_SCL(0)，所以可以直接改变Read_SDA()信号
		//dat=dat<<1;
		DELAY_US(5);
		Set_SCL(1);
		DELAY_US(5);//建立时间>4.7us
		Set_SCL(0);
		DELAY_US(5);//时间大于4us
	}
	Set_SDA(1);
	DELAY_US(5);
	Set_SCL(1);
	while(Read_SDA())//等待应答，也就是等待从设备把Read_SDA()拉低
	{
		b++;
		if(b>2000)	 //如果超过2000us没有应答发送失败，或者为非应答，表示接收结束
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
* 函数名         : I2cReadByte()
* 函数功能		   : 使用I2c读取一个字节
* 输入           : 无
* 输出         	 : dat
* 备注           : 接收完一个字节Set_SCL(0),Set_Read_SDA()(1).
*******************************************************************************/

unsigned char I2cReadByte()
{
	unsigned char a=0,dat=0;
	Set_SDA(1);			//起始和发送一个字节之后SCL都是0
	DELAY_US(5);
	for(a=0;a<8;a++)//接收8个字节
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
* 函数名         : void At24c02Write(unsigned char addr,unsigned char dat)
* 函数功能		   : 往24c02的一个地址写入一个数据
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void At24c02Write(unsigned char addr,unsigned char dat)
{
	I2cStart();
	I2cSendByte(0xa0);//发送写器件地址
	I2cSendByte(addr);//发送要写入内存地址
	I2cSendByte(dat);	//发送数据
	I2cStop();
}
/*******************************************************************************
* 函数名         : unsigned char At24c02Read(unsigned char addr)
* 函数功能		   : 读取24c02的一个地址的一个数据
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

unsigned char At24c02Read(unsigned char addr)
{
	unsigned char num;
	I2cStart();
	I2cSendByte(0xa0); //发送写器件地址
	I2cSendByte(addr); //发送要读取的地址
	I2cStart();
	I2cSendByte(0xa1); //发送读器件地址
	num=I2cReadByte(); //读取数据
	I2cStop();
	return num;
}


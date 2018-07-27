// TI File $Revision: /main/2 $
// Checkin $Date: April 29, 2005   11:08:40 $
//###########################################################################
//
// FILE:	DSP281x_Sci.c
//
// TITLE:	DSP281x SCI Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP281x C/C++ Header Files V1.20 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File



//---------------------------------------------------------------------------
// InitSPI: 
//---------------------------------------------------------------------------
// This function initializes the SCI(s) to a known state.
//
void InitSci(void)
{

/*	// Initialize SCI-A:
	//通信格式，每10帧数据1位起始，8位数据，1位结束位
 	SciaRegs.SCICCR.bit.ADDRIDLE_MODE = 0;
	SciaRegs.SCICCR.bit.PARITYENA = 0;
	SciaRegs.SCICCR.bit.SCICHAR = 7;
	SciaRegs.SCICCR.bit.STOPBITS = 0;

	//接收错误中断
	SciaRegs.SCICTL1.bit.RXENA = 1;
	SciaRegs.SCICTL1.bit.SWRESET = 0;
	SciaRegs.SCICTL1.bit.RXERRINTENA = 0;
	SciaRegs.SCICTL1.bit.TXENA = 1;
	SciaRegs.SCICTL2.bit.RXBKINTENA =1;
	//SciaRegs.SCICTL2.bit.TXINTENA =1;//禁止发送中断

	//4800波特率 2400|4800|9600|19200|38400
	//		0x07A0|0x03D0|0x01E7|0x00F3|0x0079
	SciaRegs.SCIHBAUD = 0x0003;
	SciaRegs.SCILBAUD = 0x00D0;

	SciaRegs.SCIFFTX.bit.SCIRST = 1;
	//SciaRegs.SCIPRI.bit.SOFT = 0;
	SciaRegs.SCIPRI.bit.FREE = 1;

	//使能SCI工作
	SciaRegs.SCICTL1.bit.SWRESET = 1;
*/

	// Initialize SCI-B:
	//通信格式，每10帧数据1位起始，8位数据，1位结束位
 	ScibRegs.SCICCR.bit.ADDRIDLE_MODE = 0;
	ScibRegs.SCICCR.bit.PARITYENA = 0;
	ScibRegs.SCICCR.bit.SCICHAR = 7;
	ScibRegs.SCICCR.bit.STOPBITS = 0;

	//接收错误中断
	ScibRegs.SCICTL1.bit.SWRESET = 0;
	ScibRegs.SCICTL1.bit.RXENA = 1;
	ScibRegs.SCICTL1.bit.RXERRINTENA = 0;
	ScibRegs.SCICTL1.bit.TXENA = 1;
	ScibRegs.SCICTL2.bit.RXBKINTENA =1;
	SciaRegs.SCICTL2.bit.TXINTENA =1;//禁止发送中断

	//4800波特率 2400|4800|9600|19200|38400
	//		0x07A0|0x03D0|0x01E7|0x00F3|0x0079
	ScibRegs.SCIHBAUD = 0x0003;
	ScibRegs.SCILBAUD = 0x00D0;

	ScibRegs.SCIFFTX.bit.SCIRST = 1;
	//SciaRegs.SCIPRI.bit.SOFT = 0;
	//ScibRegs.SCIPRI.bit.FREE = 1;

	//使能SCI工作
	ScibRegs.SCICTL1.bit.SWRESET = 1;

}	

Uint8 rec_data;//串口接收到的数据
Uint8 state_flag = 0;//通信协议解析状态标志，初始化为0
volatile Uint8 retval=0;//通信协议解析函数返回值，初始化为0
Uint8 cmd;//接收到的指令码
Uint8 Data[2] = {0,0};//数据码
Uint8 data_count;//数据长度码

Uint8 cmd_code;//当前请求的指令数据

Uint16 check_delay =0;

Uint8 recdata_sum =0;//异或校验
Uint8 lencnt = 0;//数据长度计数器
Uint8 packet_style =0;//0 请求数据包 1修改数据包 命令码

void Data_Analysis()
{
	////服务器数据包构成0x2A,0x2B,0x2C,命令码，地址码,指令码，数据长度码,数据码,数据码,校验码,0x1D  检验码=命令码^地址码^指令码^数据长度码^数据码1^数据码2
	rec_data = ScibRegs.SCIRXBUF.bit.RXDT;
	if(retval == 1)//有接收包未处理，则直接忽略
	{
		return ;
	}
	switch (state_flag)
	{
		case 0:
		{
			if(rec_data == 0x2A)     // 是否帧头第一个数据
				state_flag = 1;
			else
				state_flag = 0;    // 标志复位
			break;
		}
		case 1:
		{
			if(rec_data == 0x2B)     // 是否帧头第二个数据
				state_flag = 2;
			else
				state_flag = 0;    // 标志复位
			break;
		}
		case 2:
		{
			if(rec_data == ID)    // 判断目的地址是否正确
			{
				state_flag = 3;
			}
			else
				state_flag = 0;   // 标志复位
			break;
		}
		case 3:
		{
			if(rec_data ==0x01)
			{
				// 请求数据
				state_flag = 4;
				packet_style = 1;
				recdata_sum = rec_data;
			}
			else if(rec_data == 0x00)
			{
				state_flag = 4;
				packet_style =0;
				recdata_sum = rec_data;
			}
			else
			{
				state_flag =0;
			}
			break;
		}
		case 4:
			if(rec_data >99)
			{
				state_flag = 0;
			}
			else
			{
				state_flag = 5;
				cmd=rec_data;  //指令码存储
				recdata_sum ^= rec_data;
			}
			break;
		case 5:
		{
			lencnt = 0;  //数据长度计数器清零
			data_count=rec_data;  //数据长度码存储
			recdata_sum^=rec_data;  //异或
			Data[0]=0;
			Data[1]=0;
			if (data_count!=0)  //后面有数据码
				state_flag=6;
			else
				state_flag=0;
			break;
		}
		case 6:
			Data[lencnt++] = rec_data;//数据码保存
			recdata_sum^=rec_data;  //异或
			if(lencnt==data_count)
			{
				state_flag=7;
				lencnt =0;
			}
			else
			{
				state_flag =6;
			}
			break;
		case 7:
		{
			if(recdata_sum==rec_data)   //数据校验，判断累加和是否相等
				state_flag=8;
			else
			{
				state_flag=0;
			}
			break;
		}
		case 8:
		{
			if (rec_data==0x2D)
			{
				retval=1;   //置接收成功标志，数据包传送成功。
			}
			state_flag=0;
			break;
		}
	}
}
//发送一个数据包给客户端
void Usart_Cmd_Send(Uint8 index,int16 value)
{
	//服务器数据包构成0x1A,0x1B,0x1C,地址码,指令码,符号码,数据长度码(不包含符号),数据码,数据码,数据码,校验码,0x1D  检验码最大3+27+67=97
	Send_Char(0x1A);
	Send_Char(0x1B);
	Send_Char(0x1C);
	Send_Char(0x01);
	Send_Char(index);
	Send_Char(0x02);
	Send_Char(value>>8);
	Send_Char(value);
	Send_Char(index^0x02^(value>>8)^value);
	Send_Char(0x1D);
}
void Usart_Cmd_Scan()
{
	int16 data_value;
	if(retval==1)
	{
		data_value = (Data[0]<<8)|Data[1];
		if(packet_style ==0)//请求数据
		{
			if(cmd>=50)
			{
				SendMenu2Data(cmd-50);
			}
			else
			{
				CompareMenu1Data(cmd);
			}

		}
		else//修改数据
		{
			if(cmd>=50)
			{
				CompareMenu2Data(cmd-50,data_value);
			}
		}
		retval =0;
	}
}
void Send_Char(Uint8 ch)
{
	//while(SciaRegs.SCICTL2.bit.TXRDY == 0);
	//SciaRegs.SCITXBUF=ch;

	while(ScibRegs.SCICTL2.bit.TXRDY == 0);
		ScibRegs.SCITXBUF=ch;
}
//===========================================================================
// No more.
//===========================================================================

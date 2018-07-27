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
	//ͨ�Ÿ�ʽ��ÿ10֡����1λ��ʼ��8λ���ݣ�1λ����λ
 	SciaRegs.SCICCR.bit.ADDRIDLE_MODE = 0;
	SciaRegs.SCICCR.bit.PARITYENA = 0;
	SciaRegs.SCICCR.bit.SCICHAR = 7;
	SciaRegs.SCICCR.bit.STOPBITS = 0;

	//���մ����ж�
	SciaRegs.SCICTL1.bit.RXENA = 1;
	SciaRegs.SCICTL1.bit.SWRESET = 0;
	SciaRegs.SCICTL1.bit.RXERRINTENA = 0;
	SciaRegs.SCICTL1.bit.TXENA = 1;
	SciaRegs.SCICTL2.bit.RXBKINTENA =1;
	//SciaRegs.SCICTL2.bit.TXINTENA =1;//��ֹ�����ж�

	//4800������ 2400|4800|9600|19200|38400
	//		0x07A0|0x03D0|0x01E7|0x00F3|0x0079
	SciaRegs.SCIHBAUD = 0x0003;
	SciaRegs.SCILBAUD = 0x00D0;

	SciaRegs.SCIFFTX.bit.SCIRST = 1;
	//SciaRegs.SCIPRI.bit.SOFT = 0;
	SciaRegs.SCIPRI.bit.FREE = 1;

	//ʹ��SCI����
	SciaRegs.SCICTL1.bit.SWRESET = 1;
*/

	// Initialize SCI-B:
	//ͨ�Ÿ�ʽ��ÿ10֡����1λ��ʼ��8λ���ݣ�1λ����λ
 	ScibRegs.SCICCR.bit.ADDRIDLE_MODE = 0;
	ScibRegs.SCICCR.bit.PARITYENA = 0;
	ScibRegs.SCICCR.bit.SCICHAR = 7;
	ScibRegs.SCICCR.bit.STOPBITS = 0;

	//���մ����ж�
	ScibRegs.SCICTL1.bit.SWRESET = 0;
	ScibRegs.SCICTL1.bit.RXENA = 1;
	ScibRegs.SCICTL1.bit.RXERRINTENA = 0;
	ScibRegs.SCICTL1.bit.TXENA = 1;
	ScibRegs.SCICTL2.bit.RXBKINTENA =1;
	SciaRegs.SCICTL2.bit.TXINTENA =1;//��ֹ�����ж�

	//4800������ 2400|4800|9600|19200|38400
	//		0x07A0|0x03D0|0x01E7|0x00F3|0x0079
	ScibRegs.SCIHBAUD = 0x0003;
	ScibRegs.SCILBAUD = 0x00D0;

	ScibRegs.SCIFFTX.bit.SCIRST = 1;
	//SciaRegs.SCIPRI.bit.SOFT = 0;
	//ScibRegs.SCIPRI.bit.FREE = 1;

	//ʹ��SCI����
	ScibRegs.SCICTL1.bit.SWRESET = 1;

}	

Uint8 rec_data;//���ڽ��յ�������
Uint8 state_flag = 0;//ͨ��Э�����״̬��־����ʼ��Ϊ0
volatile Uint8 retval=0;//ͨ��Э�������������ֵ����ʼ��Ϊ0
Uint8 cmd;//���յ���ָ����
Uint8 Data[2] = {0,0};//������
Uint8 data_count;//���ݳ�����

Uint8 cmd_code;//��ǰ�����ָ������

Uint16 check_delay =0;

Uint8 recdata_sum =0;//���У��
Uint8 lencnt = 0;//���ݳ��ȼ�����
Uint8 packet_style =0;//0 �������ݰ� 1�޸����ݰ� ������

void Data_Analysis()
{
	////���������ݰ�����0x2A,0x2B,0x2C,�����룬��ַ��,ָ���룬���ݳ�����,������,������,У����,0x1D  ������=������^��ַ��^ָ����^���ݳ�����^������1^������2
	rec_data = ScibRegs.SCIRXBUF.bit.RXDT;
	if(retval == 1)//�н��հ�δ������ֱ�Ӻ���
	{
		return ;
	}
	switch (state_flag)
	{
		case 0:
		{
			if(rec_data == 0x2A)     // �Ƿ�֡ͷ��һ������
				state_flag = 1;
			else
				state_flag = 0;    // ��־��λ
			break;
		}
		case 1:
		{
			if(rec_data == 0x2B)     // �Ƿ�֡ͷ�ڶ�������
				state_flag = 2;
			else
				state_flag = 0;    // ��־��λ
			break;
		}
		case 2:
		{
			if(rec_data == ID)    // �ж�Ŀ�ĵ�ַ�Ƿ���ȷ
			{
				state_flag = 3;
			}
			else
				state_flag = 0;   // ��־��λ
			break;
		}
		case 3:
		{
			if(rec_data ==0x01)
			{
				// ��������
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
				cmd=rec_data;  //ָ����洢
				recdata_sum ^= rec_data;
			}
			break;
		case 5:
		{
			lencnt = 0;  //���ݳ��ȼ���������
			data_count=rec_data;  //���ݳ�����洢
			recdata_sum^=rec_data;  //���
			Data[0]=0;
			Data[1]=0;
			if (data_count!=0)  //������������
				state_flag=6;
			else
				state_flag=0;
			break;
		}
		case 6:
			Data[lencnt++] = rec_data;//�����뱣��
			recdata_sum^=rec_data;  //���
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
			if(recdata_sum==rec_data)   //����У�飬�ж��ۼӺ��Ƿ����
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
				retval=1;   //�ý��ճɹ���־�����ݰ����ͳɹ���
			}
			state_flag=0;
			break;
		}
	}
}
//����һ�����ݰ����ͻ���
void Usart_Cmd_Send(Uint8 index,int16 value)
{
	//���������ݰ�����0x1A,0x1B,0x1C,��ַ��,ָ����,������,���ݳ�����(����������),������,������,������,У����,0x1D  ���������3+27+67=97
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
		if(packet_style ==0)//��������
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
		else//�޸�����
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

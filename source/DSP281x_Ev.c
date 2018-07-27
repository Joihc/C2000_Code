// TI File $Revision: /main/2 $
// Checkin $Date: April 29, 2005   11:10:23 $
//###########################################################################
//
// FILE:	DSP281x_Ev.c
//
// TITLE:	DSP281x Event Manager Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP281x C/C++ Header Files V1.20 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File

//��С��λ�2.6us
#define SMALL_RATIO 6

volatile Uint32 T1PR_Value;
volatile Uint32  Duty_Ratio;
//��ѹ������λ���С��SMALL_RATIO
bool RatioTooSmall();
//---------------------------------------------------------------------------
// InitEv: 
//---------------------------------------------------------------------------
// This function initializes to a known state.
//
void InitEv(void)
{
	T1PR_Value = T1PR_MIN;
	Duty_Ratio = T1PR_Value-10000;
	//EVA
	EvaRegs.T1CNT = 0x0000;//��ʱ��1�������ĵ�ǰֵ
	EvaRegs.T1PR =T1PR_Value; //T1PR_Value;//���Ǹ�ʱ������ֵ

	EvaRegs.CMPR1=2;
	EvaRegs.CMPR2=Duty_Ratio;
	EvaRegs.CMPR3=2;

	EvaRegs.T1CON.bit.TMODE=1;//������������

	EvaRegs.GPTCONA.bit.TCMPOE = 1;
	//EvaRegs.GPTCONA.bit.T1CMPOE =1;

	EvaRegs.COMCONA.bit.CLD =1;
	//EvaRegs.COMCONA.bit.ACTRLD =1;

	EvaRegs.ACTRA.bit.CMP1ACT =2;
	EvaRegs.ACTRA.bit.CMP2ACT =1;
	EvaRegs.ACTRA.bit.CMP3ACT =2;
	EvaRegs.ACTRA.bit.CMP4ACT =1;
	EvaRegs.ACTRA.bit.CMP5ACT =2;//1�˿ں�5���һ��
	EvaRegs.ACTRA.bit.CMP6ACT =1;

	EvaRegs.DBTCONA.bit.DBTPS =5;
	EvaRegs.DBTCONA.bit.DBT = 6;//����2.56us
	EvaRegs.DBTCONA.bit.EDBT1 =1;
	EvaRegs.DBTCONA.bit.EDBT2 =1;
	EvaRegs.DBTCONA.bit.EDBT3 =1;

	//��λ�����жϱ�־
	EvaRegs.EVAIFRA.all=0xFFFF;
	EvaRegs.EVAIFRB.all =0xFFFF;
	EvaRegs.EVAIFRC.all =0xFFFF;

	//ʹ��
	EvaRegs.EVAIMRA.bit.T1PINT =1;//��ʱ��1�����ж�
	EvaRegs.EVAIMRA.bit.T1UFINT =1;//��ʱ��1�����ж�
	EvaRegs.EVAIMRA.bit.PDPINTA=1;//�ⲿ��ͣ�ж�

	EvaRegs.T1CON.bit.TENABLE = 1;//������ʱ��
	EvaRegs.COMCONA.bit.CENABLE = 1;
	EvaRegs.COMCONA.bit.FCOMPOE = 1;//�����߼���ƽ�任
}	
void SetPWMStatus(bool status)
{
	if(status)
	{
		EvaRegs.ACTRA.bit.CMP1ACT =2;
		EvaRegs.ACTRA.bit.CMP2ACT =1;
		EvaRegs.ACTRA.bit.CMP3ACT =2;
		EvaRegs.ACTRA.bit.CMP4ACT =1;
		EvaRegs.ACTRA.bit.CMP5ACT =2;//1�˿ں�5���һ��
		EvaRegs.ACTRA.bit.CMP6ACT =1;
	}
	else
	{//ǿ�Ƶ�
		EvaRegs.ACTRA.bit.CMP1ACT =0;
		EvaRegs.ACTRA.bit.CMP2ACT =0;
		EvaRegs.ACTRA.bit.CMP3ACT =0;
		EvaRegs.ACTRA.bit.CMP4ACT =0;
		EvaRegs.ACTRA.bit.CMP5ACT =0;
		EvaRegs.ACTRA.bit.CMP6ACT =0;
	}
}
// MIN_HZ
// MAX_HZ
void SetEvaFrequency(bool plus)
{
	plus?T1PR_Value++:T1PR_Value--;
	if(T1PR_Value>T1PR_MAX)
	{
		T1PR_Value = T1PR_MAX;
	}
	else if(T1PR_Value<T1PR_MIN)
	{
		T1PR_Value = T1PR_MIN;
	}
	if(Duty_Ratio >T1PR_Value-1)
	{
		Duty_Ratio=T1PR_Value-1;
	}
	else if(Duty_Ratio <1)
	{
		Duty_Ratio = 1;
	}
	EvaRegs.T1PR = T1PR_Value;//���Ǹ�ʱ������ֵ
}
//��λ��
void SetEvaDutyRatio(bool plus)
{
	plus?Duty_Ratio++:Duty_Ratio--;
	if(Duty_Ratio >T1PR_Value-1)
	{
		Duty_Ratio=T1PR_Value-1;
	}
	else if(Duty_Ratio <1)
	{
		Duty_Ratio = 1;
	}
}
void T1Pint()
{
	EvaRegs.CMPR1=1;
	EvaRegs.CMPR2=T1PR_Value-Duty_Ratio;
	EvaRegs.CMPR3=1;
	EvaRegs.EVAIFRA.bit.T1PINT =1;//��λ��ʱ��1�����жϱ�־
}
void T1Ufint()
{
	EvaRegs.CMPR1=T1PR_Value-1;
	EvaRegs.CMPR2=Duty_Ratio;
	EvaRegs.CMPR3=T1PR_Value-1;
	EvaRegs.EVAIFRA.bit.T1UFINT =1;//��λ��ʱ��1�����ж�
}
void EVAPDPINTA()
{
	if(EvaRegs.COMCONA.bit.PDPINTASTATUS == 0)
	{
		SetPWMStatus(false);
	}
}
//��С��λ�2.6us
#define SMALL_RATIO 6
//��ѹ������λ���С��SMALL_RATIO
bool RatioTooSmall()
{
	return true;
}
//�����������
void SetOutPower(bool plus)
{
	if(plus)
	{//���ӹ���
		if(RatioTooSmall())
		{//��λ���С
			SetEvaDutyRatio(true);//����ռ�ձ�
		}
		else
		{
			SetEvaFrequency(false);//��СƵ��
		}
	}
	else
	{//��С����
		if(RatioTooSmall())
		{//��λ���С
			SetEvaFrequency(false);//����Ƶ��
		}
		else
		{
			SetEvaDutyRatio(false);//��Сռ�ձ�
		}
	}

}
//===========================================================================
// No more.
//===========================================================================

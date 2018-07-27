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

//最小相位差，2.6us
#define SMALL_RATIO 6

volatile Uint32 T1PR_Value;
volatile Uint32  Duty_Ratio;
//电压电流相位差不能小于SMALL_RATIO
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
	EvaRegs.T1CNT = 0x0000;//定时器1计数器的当前值
	EvaRegs.T1PR =T1PR_Value; //T1PR_Value;//爹那个时期周期值

	EvaRegs.CMPR1=2;
	EvaRegs.CMPR2=Duty_Ratio;
	EvaRegs.CMPR3=2;

	EvaRegs.T1CON.bit.TMODE=1;//连续增减计数

	EvaRegs.GPTCONA.bit.TCMPOE = 1;
	//EvaRegs.GPTCONA.bit.T1CMPOE =1;

	EvaRegs.COMCONA.bit.CLD =1;
	//EvaRegs.COMCONA.bit.ACTRLD =1;

	EvaRegs.ACTRA.bit.CMP1ACT =2;
	EvaRegs.ACTRA.bit.CMP2ACT =1;
	EvaRegs.ACTRA.bit.CMP3ACT =2;
	EvaRegs.ACTRA.bit.CMP4ACT =1;
	EvaRegs.ACTRA.bit.CMP5ACT =2;//1端口和5输出一样
	EvaRegs.ACTRA.bit.CMP6ACT =1;

	EvaRegs.DBTCONA.bit.DBTPS =5;
	EvaRegs.DBTCONA.bit.DBT = 6;//死区2.56us
	EvaRegs.DBTCONA.bit.EDBT1 =1;
	EvaRegs.DBTCONA.bit.EDBT2 =1;
	EvaRegs.DBTCONA.bit.EDBT3 =1;

	//复位所有中断标志
	EvaRegs.EVAIFRA.all=0xFFFF;
	EvaRegs.EVAIFRB.all =0xFFFF;
	EvaRegs.EVAIFRC.all =0xFFFF;

	//使能
	EvaRegs.EVAIMRA.bit.T1PINT =1;//定时器1周期中断
	EvaRegs.EVAIMRA.bit.T1UFINT =1;//定时器1下溢中断
	EvaRegs.EVAIMRA.bit.PDPINTA=1;//外部急停中断

	EvaRegs.T1CON.bit.TENABLE = 1;//开启定时器
	EvaRegs.COMCONA.bit.CENABLE = 1;
	EvaRegs.COMCONA.bit.FCOMPOE = 1;//开启逻辑电平变换
}	
void SetPWMStatus(bool status)
{
	if(status)
	{
		EvaRegs.ACTRA.bit.CMP1ACT =2;
		EvaRegs.ACTRA.bit.CMP2ACT =1;
		EvaRegs.ACTRA.bit.CMP3ACT =2;
		EvaRegs.ACTRA.bit.CMP4ACT =1;
		EvaRegs.ACTRA.bit.CMP5ACT =2;//1端口和5输出一样
		EvaRegs.ACTRA.bit.CMP6ACT =1;
	}
	else
	{//强制低
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
	EvaRegs.T1PR = T1PR_Value;//爹那个时期周期值
}
//相位差
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
	EvaRegs.EVAIFRA.bit.T1PINT =1;//复位定时器1周期中断标志
}
void T1Ufint()
{
	EvaRegs.CMPR1=T1PR_Value-1;
	EvaRegs.CMPR2=Duty_Ratio;
	EvaRegs.CMPR3=T1PR_Value-1;
	EvaRegs.EVAIFRA.bit.T1UFINT =1;//复位定时器1下溢中断
}
void EVAPDPINTA()
{
	if(EvaRegs.COMCONA.bit.PDPINTASTATUS == 0)
	{
		SetPWMStatus(false);
	}
}
//最小相位差，2.6us
#define SMALL_RATIO 6
//电压电流相位差不能小于SMALL_RATIO
bool RatioTooSmall()
{
	return true;
}
//输出功率增加
void SetOutPower(bool plus)
{
	if(plus)
	{//增加功率
		if(RatioTooSmall())
		{//相位差过小
			SetEvaDutyRatio(true);//增加占空比
		}
		else
		{
			SetEvaFrequency(false);//减小频率
		}
	}
	else
	{//减小功率
		if(RatioTooSmall())
		{//相位差过小
			SetEvaFrequency(false);//增加频率
		}
		else
		{
			SetEvaDutyRatio(false);//减小占空比
		}
	}

}
//===========================================================================
// No more.
//===========================================================================

// TI File $Revision: /main/2 $
// Checkin $Date: April 29, 2005   11:11:45 $
//###########################################################################
//
// FILE:	DSP281x_Adc.c
//
// TITLE:	DSP281x ADC Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP281x C/C++ Header Files V1.20 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File

#define ADC_usDELAY  8000L
#define ADC_usDELAY2 20L

#define ADC_MODCLK 0x3   // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3)         = 25MHz
#define ADC_CKPS   0x3   // ADC module clock = HSPCLK/2*ADC_CKPS   = 25MHz/(3*2) = 4.17MHz
#define ADC_SHCLK  0xf   // S/H width in ADC module periods                      = 16 ADC clocks


struct FirQueue switch_adc;//开关队列

//---------------------------------------------------------------------------
// InitAdc: 
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
void InitAdc(void)
{
	extern void DSP28x_usDelay(Uint32 Count);
	
    // To powerup the ADC the ADCENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap and reference circuitry.
    // After a 5ms delay the rest of the ADC can be powered up. After ADC
    // powerup, another 20us delay is required before performing the first
    // ADC conversion. Please note that for the delay function below to
    // operate correctly the CPU_CLOCK_SPEED define statement in the
    // DSP28_Examples.h file must contain the correct CPU clock period in
    // nanoseconds. For example:
	AdcRegs.ADCTRL1.bit.RESET=1;//复位
	DELAY_US(20);      //至少等待12周期以使复位有效

	AdcRegs.ADCTRL3.bit.ADCBGRFDN = 0x3;	// Power up bandgap/reference circuitry
	DELAY_US(ADC_usDELAY);                  // Delay before powering up rest of ADC
	AdcRegs.ADCTRL3.bit.ADCPWDN = 1;		// Power up rest of ADC
	DELAY_US(ADC_usDELAY2);                 // Delay after powering up ADC

	// Specific ADC setup for this example:
   AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;
   AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;

	AdcRegs.ADCTRL1.bit.SUSMOD =0x03;
    AdcRegs.ADCTRL1.bit.SEQ_CASC=1;
   	AdcRegs.ADCTRL3.bit.SMODE_SEL=0;
    AdcRegs.ADCMAXCONV.all=0x0000;//转换通道数
   //AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;  // Enable SEQ1 interrupt (every EOS)

   FirQueueInit(&switch_adc);
}	

Uint16 StartTranslateAdc(Uint8 index)
{
	//if(AdcRegs.ADCST.bit.SEQ1_BSY)
	//{
	//	AdcRegs.ADCTRL2.bit.SOC_SEQ1 =1;
	//}
	Uint16 value =0;
	switch(index)
	{
	case 0:
		AdcRegs.ADCCHSELSEQ1.all = 0x00;//
		AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;//
		AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
		while(AdcRegs.ADCST.bit.SEQ1_BSY);//转换结束
		FirQueueIn(&switch_adc,AdcRegs.ADCRESULT0>>4);
		value = FirQueueCal(&switch_adc);
		break;
	default:
		break;
	}
	return value;
}
//===========================================================================
// No more.
//===========================================================================

// TI File $Revision: /main/2 $
// Checkin $Date: April 29, 2005   11:10:14 $
//###########################################################################
//
// FILE:	DSP281x_Gpio.c
//
// TITLE:	DSP281x General Purpose I/O Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP281x C/C++ Header Files V1.20 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File

//---------------------------------------------------------------------------
// InitGpio: 
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known state.
//
void InitGpio(void)
{

// Set GPIO A port pins,AL(Bits 7:0)(input)-AH(Bits 15:8) (output) 8bits
// Input Qualifier =0, none

      EALLOW;

     //SCIA
//     GpioMuxRegs.GPFMUX.bit.SCITXDA_GPIOF4 = 1;
//     GpioMuxRegs.GPFMUX.bit.SCIRXDA_GPIOF5 = 1;

     //SCIB
     GpioMuxRegs.GPGMUX.bit.SCITXDB_GPIOG4 = 1;
     GpioMuxRegs.GPGMUX.bit.SCIRXDB_GPIOG5 = 1;

     //PWM
     GpioMuxRegs.GPAMUX.bit.PWM1_GPIOA0 =1;
     GpioMuxRegs.GPAMUX.bit.PWM2_GPIOA1 =1;
     GpioMuxRegs.GPAMUX.bit.PWM3_GPIOA2 =1;
     GpioMuxRegs.GPAMUX.bit.PWM4_GPIOA3 =1;
     GpioMuxRegs.GPAMUX.bit.PWM5_GPIOA4 =1;
     GpioMuxRegs.GPAMUX.bit.PWM6_GPIOA5 =1;

     //SPI
     GpioMuxRegs.GPFMUX.bit.SPICLKA_GPIOF2 = 1;
     GpioMuxRegs.GPFMUX.bit.SPISIMOA_GPIOF0 = 1;
     GpioMuxRegs.GPFMUX.bit.SPISOMIA_GPIOF1 = 1	;

     GpioMuxRegs.GPFMUX.bit.SPISTEA_GPIOF3 = 0;

     GpioMuxRegs.GPFDIR.bit.GPIOF3 = 1;
     GpioDataRegs.GPFDAT.bit.GPIOF3 =1;


     //I2C
     //GpioMuxRegs.GPFMUX.bit.SPICLKA_GPIOF2 =0;//SDA
     //GpioMuxRegs.GPFMUX.bit.SPISTEA_GPIOF3 =0;//SCL


     //SPI 31855
     GpioMuxRegs.GPFMUX.bit.MDRA_GPIOF13 =0;//CS
     GpioMuxRegs.GPFMUX.bit.MDXA_GPIOF12 =0;//CLK
     GpioMuxRegs.GPFMUX.bit.MFSRA_GPIOF11 =0;//D0

     GpioMuxRegs.GPFDIR.bit.GPIOF12 = 1;
     GpioMuxRegs.GPFDIR.bit.GPIOF13 = 1;
     GpioMuxRegs.GPFDIR.bit.GPIOF11 = 0;

     GpioMuxRegs.GPFMUX.bit.MFSXA_GPIOF10 =0;//CS
     GpioMuxRegs.GPFMUX.bit.MCLKRA_GPIOF9 =0;//CLK
     GpioMuxRegs.GPFMUX.bit.MCLKXA_GPIOF8 =0;//D0

     GpioMuxRegs.GPFDIR.bit.GPIOF9 = 1;
     GpioMuxRegs.GPFDIR.bit.GPIOF10 = 1;
     GpioMuxRegs.GPFDIR.bit.GPIOF8 = 0;
     EDIS;


}	
//===========================================================================
// No more.
//===========================================================================

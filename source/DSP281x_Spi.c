// TI File $Revision: /main/2 $
// Checkin $Date: April 29, 2005   11:08:24 $
//###########################################################################
//
// FILE:   DSP281x_Spi.c
//
// TITLE:  DSP281x SPI Initialization & Support Functions.
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
// This function initializes the SPI(s) to a known state.
//
void InitSpi(void)
{
   // Initialize SPI-A:
	   SpiaRegs.SPICCR.bit.SPISWRESET=0; // Reset SPI

	   SpiaRegs.SPICCR.all=0x0007;       //8-bit character, close Loopback mode
	   SpiaRegs.SPICTL.all=0x0006;       //Interrupt enabled, Master/Slave XMIT enabled
	   SpiaRegs.SPISTS.all=0x0000;
	   SpiaRegs.SPIBRR=30;           // Baud rate

	   SpiaRegs.SPICCR.bit.SPISWRESET=1;  // Enable SPI



   //tbd...
 
}

#define SPI_CS (GpioDataRegs.GPFDAT.bit.GPIOF3)
#define SPI_READ 	(0x0300)
#define SPI_WRITE	(0X0200)
#define SPI_WRDI 	(0X0400)
#define SPI_WREN	(0x0600)
#define SPI_RDSR	(0x0500)
#define SPI_WRSR	(0x0100)

Uint16 Spi_Read(Uint16 addr)
{
	int16 data;
	SPI_CS =0;
	SpiaRegs.SPITXBUF = SPI_READ;
	while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
	SpiaRegs.SPIRXBUF = SpiaRegs.SPIRXBUF;
	SpiaRegs.SPITXBUF = addr<<8;
	while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
	SpiaRegs.SPIRXBUF = SpiaRegs.SPIRXBUF;
	SpiaRegs.SPITXBUF = 0;
	while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
	data = SpiaRegs.SPIRXBUF;
	SPI_CS =1;
	return data;
}

void Spi_Write(Uint16 data,Uint16 addr)
{
	Spi_Write_Enable();
	//DELAY_US(5);
	SPI_CS =0;
	SpiaRegs.SPITXBUF = SPI_WRITE;
	while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
	SpiaRegs.SPIRXBUF = SpiaRegs.SPIRXBUF;
	SpiaRegs.SPITXBUF = addr<<8;
	while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
	SpiaRegs.SPIRXBUF = SpiaRegs.SPIRXBUF;
	SpiaRegs.SPITXBUF = data<<8;
	while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
	SpiaRegs.SPIRXBUF = SpiaRegs.SPIRXBUF;
	SPI_CS =1;
	//DELAY_US(5);
	while(Spi_Read_Status()&0x0001);
}
void Spi_Write_Enable()
{
	SPI_CS = 0;
	SpiaRegs.SPITXBUF = SPI_WREN;
	while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
	SpiaRegs.SPIRXBUF = SpiaRegs.SPIRXBUF;
	SPI_CS = 1;
}
Uint16 Spi_Read_Status()
{
	Uint16 data=0;
	SPI_CS = 0;
	SpiaRegs.SPITXBUF = SPI_RDSR;
	while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
	SpiaRegs.SPIRXBUF = SpiaRegs.SPIRXBUF;
	SpiaRegs.SPITXBUF = 0;
	while(SpiaRegs.SPISTS.bit.INT_FLAG != 1);
	data = SpiaRegs.SPIRXBUF;
	SPI_CS = 1;
	return data;                        // return status register
}
//==============
//=============================================================
// No more.
//===========================================================================

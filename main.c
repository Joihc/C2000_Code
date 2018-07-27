
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File


Uint16 i = 1;
Uint8 temp_1;
Uint8 state =0;

void main(void)
{
	
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP281x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO: 
// This example function is found in the DSP281x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
   InitGpio();

   //MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);

   /*FLASH 初始化 */
   //InitFlash();
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts 
   DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.  
// This function is found in the DSP281x_PieCtrl.c file.
   InitPieCtrl();
   
// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt 
// Service Routines (ISR).  
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP281x_DefaultIsr.c.
// This function is found in DSP281x_PieVect.c.
   InitPieVectTable();

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.  
   EALLOW;
   PieVectTable.TINT0  = &cpu_timer0_isr;
  // PieVectTable.RXAINT = &scirxinta_isr;
   PieVectTable.RXBINT = &scirxintb_isr;
   //PWM中断
//   PieVectTable.PDPINTA = &pwm_pdpinta_isr;
   PieVectTable.T1PINT = &pwm_t1pint_isr;
   PieVectTable.T1UFINT = &pwm_t1ufint_isr;

   //ADC中断
//   PieVectTable.ADCINT = &adc_isr;
   EDIS;

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP281x_InitPeripherals.c
   InitPeripherals(); // Not required for this example


   ConfigCpuTimer(&CpuTimer0, 150, 1000000);
   StartCpuTimer0();
// Step 5. User specific code, enable interrupts:


// Enable CPU INT1 which is connected to CPU-Timer 1:
   IER |= M_INT1;//SYSCLK ADC

   IER |= M_INT9;//SCI

   IER |= M_INT2;//PWM
// Enable TINT0 in the PIE: Group 1 interrupt 7
//   PieCtrlRegs.PIEIER9.bit.INTx1 = 1;//SCIARXINTA
   PieCtrlRegs.PIEIER9.bit.INTx3 = 1;//SCIBRXINTA
   PieCtrlRegs.PIEIER1.bit.INTx7 = 1;//TINT0
   PieCtrlRegs.PIEIER2.bit.INTx4 = 1;//T1PINT 周期中断
   PieCtrlRegs.PIEIER2.bit.INTx6 = 1;//T1UFINT 下溢中断
//  PieCtrlRegs.PIEIER1.bit.INTx1 = 1;//PDPINTA 外部停止中断

//   PieCtrlRegs.PIEIER1.bit.INTx6 = 1;//ADC

// Enable global Interrupts and higher priority real-time debug events:
   EINT;   // Enable Global interrupt INTM
   ERTM;   // Enable Global realtime interrupt DBGM

   //Usart_Cmd_Send(11,1);

   //InitLocationData();//初始化数据并发送
// Step 6. IDLE loop. Just sit and loop forever (optional): 
   //GpioMuxRegs.GPFDIR.bit.GPIOF12 = 1;
   //GpioMuxRegs.GPFDIR.bit.GPIOF13 = 1;
	while(1)
	{
		Usart_Cmd_Scan();
		i++;
		if(i>StartTranslateAdc(0))
		{
			i=0;
			LED=(state?0xff:0x00);
			state = ~state;
		}
		//if(StartTranslateAdc(0)>2000)
		//{
		//	SetOutPower(true);
		//}
		//else
		//{
		//	SetOutPower(false);
		//}
		if(
				ScibRegs.SCIRXST.bit.RXERROR != 0 |
				ScibRegs.SCIRXST.bit.BRKDT != 0|
				ScibRegs.SCIRXST.bit.FE != 0|
				ScibRegs.SCIRXST.bit.OE != 0|
				ScibRegs.SCIRXST.bit.PE != 0|
				ScibRegs.SCIRXST.bit.RXWAKE != 0)
		{
			ScibRegs.SCICTL1.bit.SWRESET = 0;
			ScibRegs.SCICTL1.bit.SWRESET = 1;
		}
	}    
}

//定时器中断 1ms
interrupt void cpu_timer0_isr(void)
{
		PieCtrlRegs.PIEACK.bit.ACK1 = 1;
		//LED=i%2?0xff:0x00;
		//temp_1=readThermocouple(CELSIUS,2);
		//temp_2=readJunction(CELSIUS,2);
		//switch(temp_1)
		//{
		//case FAULT_OPEN:
		//	SendServicePacket(5,0);
		//    SendServicePacket(6,0);
		//	break;
		//case FAULT_SHORT_GND:
		//	SendServicePacket(5,1);
		//    SendServicePacket(6,1);
		//	break;
		//case FAULT_SHORT_VCC:
		//	SendServicePacket(5,2);
		//    SendServicePacket(6,2);
		//	break;
		//case NO_MAX31855:
		//	SendServicePacket(5,3);
		//    SendServicePacket(6,3);
		//	break;
		//default:
		//	SendServicePacket(5,temp_1);
		//	SendServicePacket(6,temp_2);
		//	break;
		//}
}

interrupt void scirxinta_isr(void)
{
	PieCtrlRegs.PIEACK.bit.ACK9 =1;
	if(SciaRegs.SCIRXST.bit.RXRDY)
	{
		//Data_Analysis();
	}
	//PieCtrlRegs.PIEACK.bit.ACK9 =1;
}
interrupt void scirxintb_isr(void)
{
	PieCtrlRegs.PIEACK.bit.ACK9 =1;
	if(ScibRegs.SCIRXST.bit.RXRDY)
	{
		//temp_1 = ScibRegs.SCIRXBUF.bit.RXDT;
		//while(ScibRegs.SCICTL2.bit.TXRDY == 0);
		//ScibRegs.SCITXBUF=temp_1;
		Data_Analysis();
	}
	//PieCtrlRegs.PIEACK.bit.ACK9 =1;
}
interrupt void pwm_t1pint_isr(void)
{
	PieCtrlRegs.PIEACK.bit.ACK2 =1;
	T1Pint();
//周期中断
}
interrupt void pwm_t1ufint_isr(void)
{
	PieCtrlRegs.PIEACK.bit.ACK2 =1;
	T1Ufint();
}
interrupt void pwm_pdpinta_isr(void)
{
	PieCtrlRegs.PIEACK.bit.ACK1 = 1;
	//EVAPDPINTA();
}
//interrupt void  adc_isr(void)
//{
//	TrasnlateAdc();
//	// Reinitialize for next ADC sequence
//	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
//	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
//	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

//	return;
//}
//===========================================================================
// No more.
//===========================================================================

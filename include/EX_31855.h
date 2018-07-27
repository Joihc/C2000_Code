/*
 * EX_31855.h
 *
 *  Created on: 2018年6月20日
 *      Author: hgisw
 */

#ifndef EX_31855_H_
#define EX_31855_H_

#include "config.h"

#define  SO_1 (GpioDataRegs.GPFDAT.bit.GPIOF11)//输入
#define SCK_1 (GpioDataRegs.GPFDAT.bit.GPIOF12)//输出
#define  CS_1 (GpioDataRegs.GPFDAT.bit.GPIOF13)//输出

#define  SO_2 (GpioDataRegs.GPFDAT.bit.GPIOF8)//输入
#define SCK_2 (GpioDataRegs.GPFDAT.bit.GPIOF9)//输出
#define  CS_2 (GpioDataRegs.GPFDAT.bit.GPIOF10)//输出

#define	FAULT_OPEN		10000  // No thermocouple
#define	FAULT_SHORT_GND	10001  // Thermocouple short to ground
#define	FAULT_SHORT_VCC	10002  // Thermocouple short to VCC
#define NO_MAX31855     10003  // MAX31855 not communicating


enum	unit_t
{
	CELSIUS,
	FAHRENHEIT
};

double	readThermocouple(enum unit_t	unit,Uint8 index);
double	readJunction(enum unit_t	unit,Uint8 index);

unsigned long readData_1();
unsigned long readData_2();

#endif /* EX_31855_H_ */

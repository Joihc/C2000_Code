/*
 * EX_31855.c
 *
 *  Created on: 2018年6月20日
 *      Author: hgisw
 */

#ifndef EX_31855_C_
#define EX_31855_C_

#include "EX_31855.h"

double	readThermocouple(enum unit_t	unit,Uint8 index)
{
    unsigned long data;
    double temperature;

    // Initialize temperature
    temperature = 0;

    // Shift in 32-bit of data from MAX31855
    switch(index)
    {
    case 1:data = readData_1();
    	break;
    case 2:data = readData_2();
    	break;
    default:data = readData_2();
    	break;
    }

    // Is this a MAX31855?  Bits 3 and 17 must be zero
    if (data & 0x20008)
        return NO_MAX31855;

    // If fault is detected
    if (data & 0x00010000)
    {
        // Check for fault type (3 LSB)
        switch (data & 0x00000007)
        {
            // Open circuit
            case 0x01:
                temperature = FAULT_OPEN;
                break;

            // Thermocouple short to GND
            case 0x02:
                temperature = FAULT_SHORT_GND;
                break;

            // Thermocouple short to VCC
            case 0x04:
                temperature = FAULT_SHORT_VCC;
                break;
        }
    }
    // No fault detected
    else
    {
        // Retrieve thermocouple temperature data and strip redundant data
        data = data >> 18;
        // Bit-14 is the sign
        temperature = (data & 0x00001FFF);

        // Check for negative temperature
        if (data & 0x00002000)
        {
            // 2's complement operation
            // Invert
            data = ~data;
            // Ensure operation involves lower 13-bit only
            temperature = data & 0x00001FFF;
            // Add 1 to obtain the positive number
            temperature += 1;
            // Make temperature negative
            temperature *= -1;
        }

        // Convert to Degree Celsius
        temperature *= 2.5;//放大10倍

        // If temperature unit in Fahrenheit is desired
        if (unit == FAHRENHEIT)
        {
            // Convert Degree Celsius to Fahrenheit
            temperature = (temperature * 9.0/5.0)+ 32;
        }
    }
    return (temperature);
}

/*******************************************************************************
* Name: readJunction
* Description: Read the thermocouple temperature either in Degree Celsius or
*			   Fahrenheit. Internally, the conversion takes place in the
*			   background within 100 ms. Values are updated only when the CS
*			   line is high.
*
* Argument  	Description
* =========  	===========
* 1. unit   	Unit of temperature required: CELSIUS or FAHRENHEIT
*
* Return		Description
* =========		===========
* temperature	Temperature of the cold junction either in Degree Celsius or
*				Fahrenheit.
*
*******************************************************************************/
double	readJunction(enum unit_t	unit,Uint8 index)
{
    double	temperature;
    unsigned long data;

    // Shift in 32-bit of data from MAX31855
    switch(index)
    {
    case 1:data = readData_1();
    	break;
    case 2:data = readData_2();
    	break;
    default:data = readData_2();
    	break;
    }

    // Is this a MAX31855?  Bits 3 and 17 must be zero
    if (data & 0x20008)
        return NO_MAX31855;

    // Strip fault data bits & reserved bit
    data = data >> 4;
    // Bit-12 is the sign
    temperature = (data & 0x000007FF);

    // Check for negative temperature
    if (data & 0x00000800)
    {
        // 2's complement operation
        // Invert
        data = ~data;
        // Ensure operation involves lower 11-bit only
        temperature = data & 0x000007FF;
        // Add 1 to obtain the positive number
        temperature += 1;
        // Make temperature negative
        temperature *= -1;
    }

    // Convert to Degree Celsius
    temperature *= 0.625;//放大10倍

    // If temperature unit in Fahrenheit is desired
    if (unit == FAHRENHEIT)
    {
        // Convert Degree Celsius to Fahrenheit
        temperature = (temperature * 9.0/5.0)+ 32;
    }

    // Return the temperature
    return (temperature);
}

/*******************************************************************************
* Name: readData
* Description: Shift in 32-bit of data from MAX31855 chip. Minimum clock pulse
*			   width is 100 ns. No delay is required in this case.
*
* Argument  	Description
* =========  	===========
* 1. NIL
*
* Return		Description
* =========		===========
* data			32-bit of data acquired from the MAX31855 chip.
*
*******************************************************************************/
unsigned long readData_1()
{
    int bitCount;
    unsigned long data = 0;

    CS_1 = 1;

    DELAY_US(10);

    SCK_1=0;
    // Select the MAX31855 chip
    CS_1 = 0;
    DELAY_US(10);
    // Shift in 32-bit of data
    for (bitCount = 31; bitCount >= 0; bitCount--)
    {
    	SCK_1=1;
    	DELAY_US(10);
        // If data bit is high
        if (SO_1)
        {
            // Need to type cast data type to unsigned long, else compiler will
            // truncate to 16-bit
            data |= ((unsigned long)1 << bitCount);
        }

    	SCK_1=0;
    }

    // Deselect MAX31855 chip
    CS_1 = 1;

    return(data);
}
/*******************************************************************************
* Name: readData
* Description: Shift in 32-bit of data from MAX31855 chip. Minimum clock pulse
*			   width is 100 ns. No delay is required in this case.
*
* Argument  	Description
* =========  	===========
* 1. NIL
*
* Return		Description
* =========		===========
* data			32-bit of data acquired from the MAX31855 chip.
*
*******************************************************************************/
unsigned long readData_2()
{
    int bitCount;
    unsigned long data = 0;

    CS_2 = 1;

    DELAY_US(10);

    SCK_2=0;
    // Select the MAX31855 chip
    CS_2 = 0;
    DELAY_US(10);
    // Shift in 32-bit of data
    for (bitCount = 31; bitCount >= 0; bitCount--)
    {
    	SCK_2=1;
        // If data bit is high
        if (SO_2)
        {
            // Need to type cast data type to unsigned long, else compiler will
            // truncate to 16-bit
            data |= ((unsigned long)1 << bitCount);
        }

    	SCK_2=0;
    }

    // Deselect MAX31855 chip
    CS_2 = 1;

    return(data);
}
#endif /* EX_31855_C_ */

/*
 * EX_i2c.h
 *
 *  Created on: 2018Äê6ÔÂ19ÈÕ
 *      Author: hgisw
 */

#ifndef EX_I2C_H_
#define EX_I2C_H_

#include "config.h"
#ifndef EX_I2C_C_

#endif


void Set_SCL(unsigned char dat);
void Set_SDA(unsigned char dat);
unsigned char Read_SCL();
unsigned char Read_SDA();
void I2cStart();
void I2cStop();
unsigned char I2cSendByte(unsigned char dat);
unsigned char I2cReadByte();
void At24c02Write(unsigned char addr,unsigned char dat);
unsigned char At24c02Read(unsigned char addr);

#endif /* EX_I2C_H_ */

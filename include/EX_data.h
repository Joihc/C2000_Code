/*
 * EX_data..h
 *
 *  Created on: 2018��6��21��
 *      Author: hgisw
 */

#ifndef EX_DATA__H_
#define EX_DATA__H_

#include "config.h"

#define INIT_PASSWORD 1524// ��ʼ������

void InitLocationData();
void CompareMenu1Data(Uint8 index);
void SendMenu2Data(Uint8 index);
void CompareMenu2Data(Uint8 index,int16 value);
void SetDefaulLocationtData();
void WriteLocationData(Uint8 index,int16 value);
int16 ReadLocationData(Uint8 index);
void Write_Data_EERPOM(Uint8 index,int16 value);
int16 Read_Data_EEPROM(Uint8 index);

#endif /* EX_DATA__H_ */

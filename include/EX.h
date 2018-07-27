/*
 * Mydata.h
 *
 *  Created on: 2018Äê5ÔÂ22ÈÕ
 *      Author: hgisw
 */

#ifndef EX_H_
#define EX_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File


extern int16 clamp(int16 cur,int16 min,int16 max);
extern int16 my_atoi(char *str);
extern char *sstrncpy(char *dest, const char  *src, size_t n);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* EX_H_ */

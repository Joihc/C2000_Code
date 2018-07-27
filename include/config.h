/*
 * config.h
 *
 *  Created on: 2018年6月2日
 *      Author: hgisw
 */

#ifndef CONFIG_H_
#define CONFIG_H_


//LED
#define LED *(Uint16 *)0x2003	//LED地址
//EVA参数  1K到100k
#define MIN_HZ 1000
#define MAX_HZ 100000

#define T1PR_MIN  (150000000/4/MIN_HZ-1) //0分频
#define T1PR_MAX  (150000000/4/MAX_HZ-1) //0分频

#define CMPR_MAX 0.01//最大占空比
#define CMPR_MIN 0.99//最小占空比





#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EX.h"
#include "queue.h"
#include "EX_i2c.h"
#include "EX_31855.h"
#include "EX_data.h"

#endif /* CONFIG_H_ */

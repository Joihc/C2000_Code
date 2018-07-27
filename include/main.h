/*
 * main.h
 *
 *  Created on: 2018年5月12日
 *      Author: hgisw
 */

#ifndef MAIN_H_
#define MAIN_H_

#ifdef __cplusplus
extern "C" {
#endif


//SCI
interrupt void scirxinta_isr(void);
interrupt void scirxintb_isr(void);
//定时器
interrupt void cpu_timer0_isr(void);
//PWM中断
interrupt void pwm_pdpinta_isr(void);
interrupt void pwm_t1pint_isr(void);
interrupt void pwm_t1ufint_isr(void);

//interrupt void  adc_isr(void);

#include "config.h"


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* MAIN_H_ */

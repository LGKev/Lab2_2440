/*
 * timer.h
 *
 *  Created on: Sep 10, 2017
 *      Author: kk
 */

#ifndef TIMER_H_
#define TIMER_H_


void timer_a0_config(void);

/* Configures the timer for rgb cycling.
 * uses CCR[1] as the compare capture value;
 *
 * Parameters: CCR[1] value;
 *
 * */
void timer_a0_configTimer1(uint32_t);

void sysTickConfig(void);

#endif /* TIMER_H_ */

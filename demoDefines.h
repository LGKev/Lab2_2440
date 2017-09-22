/*
 * demoDefines.h
 *
 *  Created on: Sep 21, 2017
 *      Author: kk
 *
 *      Use this file to declare which definitions
 *      should be used to define multiple declarations at once.
 *      This style of header file will greatly improve ease when
 *      demonstrating many different tasks.
 *
 *      include in every .c file part of the project.
 *
 *
 */

#ifndef DEMODEFINES_H_
#define DEMODEFINES_H_

/*
 * Defines everything required for setting up the encoder
 * interrupt on port 2 pin 5. Interrupt causes globals: count and totalCount
 * to increment.
 *
 * Problem 11 of the lab.
 * */
//#define LATENCY_TEST_ISR_TO_MAIN        // PROBLEM 3
//#define PROBLEM_4                       // RGB WITH SWITCH

/* Problem 5a, defines */
//#define TIMER_65000
//#define TIMER_40000
//#define TIMER_20000
//#define TIMER_1000

#define PROBLEM_9                       // 5 hZ SQUARE WAVE
#define PROBLEM_10                      // TIMER FOR RGB
//#define PROBLEM_11                      // ENCODER

//#define CALCULATE_DISTANCE              // calculate distance



//#define PORT_1_FOR_DEBOUNCE             // Interrupt with for loop delay

//#define TIMER_A_CCR0 // set up for timer A ccr0 used mainly for RGB cycle 500ms




//#define TIMER_A_CCR1 //extra not used in this lab. but for understanding of how to set up interrupts


#ifdef LATENCY_TEST_ISR_TO_MAIN
#define LATENCY_TEST //PROBLEM 3, from main to isr

#define SYS_TICK_MEASUREMENT

#endif

#ifdef PROBLEM_4
#define RGB_SWITCH CYCLE
#endif

#ifdef PROBLEM_9
#define TIMER_A_CCR0                   //sets up timer a interrupts
#endif

#ifdef PROBLEM_10
#define RGB_TIMER_CYCLE_CONFIG
#define RGB_TIMER_CYCLE
#define TIMER_A_CCR0                   //sets up timer a interrupts
#endif


#ifdef PROBLEM_11

#define ENCODER_CONFIG //sets up encoder interrupt p2, pin 5
#define ENCODER_TEST_IR //increments count++ and totalCount++
#define N_ROTATIONS_INTERRUPT // lights led when N rotations have been triggered (14*5 = 70 interrupts)
#define N_INTERRUPTS        (70) //problem

#endif

#endif /* DEMODEFINES_H_ */

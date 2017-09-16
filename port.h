/*
 * port.h
 *
 *  Created on: Sep 10, 2017
 *      Author: kk
 */

#ifndef PORT_H_
#define PORT_H_

#define LEFT_INTERRUPT_BUTTON              (BIT1)
#define RIGHT_INTERRUPT_BUTTON             (BIT4)


/*
 * Takes no parameters.
 * Returns no parameters
 *
 * Used to set up the GPIO pins for 2 switches
 * and the RGB led on the MSP432p401 launchpad.
 *
 * */
void GPIO_configure(void);


/*Takes no parameters
 * Returns nothing
 *
 * Used to make sure the red LED1 on board
 * is set up correctly
 * toggles 20 times.
 * */
void testLED1(void);

/* Takes no parameters
 * returns nothing
 *
 * Used to configure onboard RGB led.
 *
 * */
void rgbConfig(void);

/* Takes no parameters
 * Returns nothing
 *
 * Used to test RGB led to check config.
 * uses for loop as delay.
 * */
void testRGB(void);

/*
 * Takes no parameters
 * Returns nothing
 * Used to test the interrupt latency on Port 1 Pin 7.
 * */
void latencyTestP1(void);


/*
 * Takes no parameters
 * Returns nothing
 * Used to test the interrupt latency on Port 4, pin 3.
 * */
void latencyTestP4(void);


/* Takes no Parameters
 * Returns nothing
 * cycles the RGB led one color at a time. Configures RGB
 * Uses a for loop for delay,
 * 7 colors + off
 * */
void rgbCycle(void);


#endif /* PORT_H_ */

/*
 * port.h
 *
 *  Created on: Sep 10, 2017
 *      Author: kk
 */

#ifndef PORT_H_
#define PORT_H_



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

/*
 * Takes no parameters
 * Iterates global variable COUNT each trigger of interrupt
 * Port 2 pin 5
 * LOW to HIGH trigger
 *
 * */
void encoderInterruptConfig(void);

#endif /* PORT_H_ */

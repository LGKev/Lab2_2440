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
void testRGB(void);


#endif /* PORT_H_ */

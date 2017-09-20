/*
 * port.c
 *
 *  Created on: Sep 10, 2017
 *      Author: kk
 */

// Configure the GPIO
#include "port.h"
#include "msp.h"
#include <stdint.h>

extern count;

/*====================================================================================
 * Defines for Demos
 *          1) RGB Color Shift
 *                  RFB_SWITCH_CYCLE
 * ====================================================================================
 */
//#define RGB_SWITCH_CYCLE // Problem 4 - CYCLES WITH button press. ++ and --
#define RGB_TIMER_CYCLE


/*====================================================================================
 * Additional Tests Not for Demo
 * ====================================================================================
 */
//#define LATENCY_TEST                  // Problem 3
//#define ENCODER_TEST                  // Problem 11
//#define PORT_1_FOR_DEBOUNCE           // Interrupt with for loop delay
//#define PORT_1_BOUNCE                 // Interrupt without for loop delay
void GPIO_configure(void)
{

    /* Configure Led 1 */
    P1->SEL0 &= ~BIT0;
    P1->SEL1 &= ~BIT0;
    P1->DIR |= BIT0;
    P1->OUT |= BIT0;  //on

//    /* Configure RGB led */
    P2->SEL0 &= ~(BIT0 | BIT1 | BIT2 );
    P2->SEL1 &= ~(BIT0 | BIT1 | BIT2 );
    P2->DIR |= (BIT0 | BIT1 | BIT2 );
    P2->OUT |= (BIT0 | BIT1 | BIT2 ); //HIGH
    P2->OUT &= ~(BIT0 | BIT1 | BIT2 ); //LOW

//data from encoder
    //setup in encoder config.

//  /* Right button configure */
    P1->SEL0 &= ~BIT1;
    P1->SEL1 &= ~BIT1;
    P1->DIR &= ~BIT1; //amazing that this even works. its a fluke. it is set as output right now.
    P1->REN |= BIT1;
    P1->OUT |= BIT1;
    P1->IFG &= ~BIT1; //interrupt flag to be cleared first
    P1->IES |= BIT1; //high to low
    P1->IE |= BIT1;

    /* LEFT button configure */
    P1->SEL0 &= ~BIT4;
    P1->SEL1 &= ~BIT4;
    P1->DIR &= ~BIT4;
    P1->REN |= BIT4;
    P1->OUT |= BIT4;
    P1->IFG &= ~BIT4; //interrupt flag to be cleared first
    P1->IES |= BIT4; //high to low
    P1->IE |= BIT4;

#ifdef LATENCY_TEST
    /* Configure Latency Test Output Pin */
    P1->SEL0 &= ~BIT7; //
    P1->SEL1 &= ~BIT7;
    P1->DIR |= BIT7;
    P1->OUT |= BIT7;
//
    /* Enable Interrupts in the NVIC */
#endif
    NVIC_EnableIRQ(PORT1_IRQn);

}

void PORT1_IRQHandler()
{


#ifdef LATENCY_TEST
    //latency Test
    P1->OUT ^= BIT7;//latency test pin.
    //end of test pin.
#endif

#ifdef PORT_1_FOR_DEBOUNCE
    uint32_t h = 0;
    P1->OUT ^= BIT0;
    for (h = 0; h < 10000; h++);
#endif

#ifdef PORT_1_BOUNCE
    P1->OUT ^= BIT0;
#endif

    //PART 4. DEMO TO TA
#ifdef RGB_SWITCH_CYCLE
    uint16_t wait = 0;
    for (wait = 0; wait <= 25000; wait++)
        ;

    if (P1IFG & BIT1)
    {
        P1->IFG &= ~BIT1;
        if (P2OUT == 8)
        {
            P2OUT = 0; // clear to off.
        }
        else{
        P2OUT++;
        }
    }
    if (P1IFG & BIT4)
    {
        P1->IFG &= ~BIT4;
        if (P2OUT == 0)
        {
            P2OUT = 0b111; //8
        }
        else
        {
            P2OUT--;
        }
    }
#endif

#ifdef LATENCY_TEST
    P1->OUT &= ~BIT7; //low
#endif

#ifdef  RGB_TIMER_CYCLE
    uint16_t wait = 0;
    for (wait = 0; wait <= 25000; wait++);

    //disable interrupts
    //setup the timer and start it.
    TIMER_A0->R = 0;         // Reset count, set to 0 at begining
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP; //start that timer.

    TIMER_A0->CCR[0] =11812;

    P1IFG = 0; // clear flags.

#endif

}

void testLED1()
{
    //led test red
    uint16_t delays = 0;
    uint8_t test = 0;
    for (test = 0; test < 20; test++)
    {
        P1->OUT ^= BIT0;
        for (delays = 0; delays < 10000; delays++)
            ;
    }
}

void testRGB()
{
    uint8_t color = 0b00000000;
    uint32_t delays = 0;
    uint8_t index = 0;
    for (index = 0; index < 8; index++)
    {
        P2->OUT ^= BIT1 | BIT2 | BIT3;
        for (delays = 0; delays < 40000; delays++)
            ;
    }
    // P2->OUT = 0x0; //clear it!
}

void latencyTestP1()
{
    //Latency Test
    P1->SEL0 &= ~BIT7;
    P1->SEL1 &= ~BIT7;
    P1->DIR |= BIT7;

    P1->OUT |= BIT7;

    P1->IFG |= BIT1;
    //end of latency test.
}

void latencyTestP4()
{
    //Latency Test
    P4->SEL0 &= ~BIT3;
    P4->SEL1 &= ~BIT3;
    P4->DIR |= BIT3;
    P4->IFG &= ~BIT3; //clear the bit
    P4->IES |= BIT3; //high to low, falling.
    P4->IE |= BIT3; //interrupt enable.

    P4->OUT |= BIT3;

    P4->IFG |= BIT3; //need to make sure interrupt setup.
    //end of latency test.
}

void rgbConfig()
{
    /* Configure RGB led */
    P2->SEL0 &= ~(BIT0 | BIT1 | BIT2 );
    P2->SEL1 &= ~(BIT0 | BIT1 | BIT2 );
    P2->DIR |= (BIT0 | BIT1 | BIT2 );

    P2->OUT &= ~(BIT0 | BIT1 | BIT2 ); //LOW

}

void rgbCycle()
{
    rgbConfig();
    uint8_t color = 0;
    uint32_t delay = 30000;

    P2->OUT &= ~(BIT0 | BIT1 | BIT2 ); //clear

    for (color = 0; color < 7; color++)
    {
        P2->OUT += BIT0;
        //i wonder if a simple count would work?
        if (color == 7)
        {
            P2->OUT &= ~(BIT0 | BIT1 | BIT2 ); //clear;
        }

        for (delay = 0; delay < 90000; delay++)
            ;
    }
}

void encoderInterruptConfig()
{
    P2SEL0 &= ~BIT5; //gpio
    P2SEL1 &= ~BIT5;

    //set up for pull down

    P2->REN |= BIT5;
    P2->OUT &= ~BIT5;
    P2->IFG &= ~BIT5; //interrupt flag to be cleared first
    P1->IES &= ~BIT5; //high to low trigger
    P2->IE |= BIT5;

    P2DIR &= ~BIT5; //PIN 5 INPUT

    NVIC_EnableIRQ(PORT2_IRQn);
}

//handler for encoder input, on PORT 2 pin 5.
void PORT2_IRQHandler()
{
//systick measurement
    //pin highh
    if (P2IFG & BIT5)
    {
        P1->OUT ^= BIT7;
        count++;
        P2->IFG &= ~BIT5;
    }

    // pin low
}

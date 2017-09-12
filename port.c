/*
 * port.c
 *
 *  Created on: Sep 10, 2017
 *      Author: kk
 */


// Configure the GPIO
#include "port.h"
#include "msp.h"



void GPIO_configure(void) {

    /* Configure Led 1 */
    P1->SEL0 &= ~BIT0;
    P1->SEL1 &= ~BIT0;
    P1->DIR  |=  BIT0;
    P1->OUT  &= ~BIT0;  //on


//    /* Configure RGB led */
//    P2->SEL0 &= ~(BIT0 | BIT1 | BIT2);
//    P2->SEL1 &= ~(BIT0 | BIT1 | BIT2);
//    P2->DIR  |= (BIT0 | BIT1 | BIT2);
//    P2->OUT  &= ~(BIT0 | BIT1 | BIT2); //LOW


//    //data from encoder
//    P1->SEL0 = ???;
//    P1->SEL1 = ???;
//    P1->DIR = ???;
//    P1->REN = ???;
//    P1->OUT = ???;
//    P1->IFG = ???;
//    P1->IES = ???;
//    P1->IE = ???;

//  /* Left button configure */
    P1->SEL0 &= ~BIT1;
    P1->SEL1 &= ~BIT1;
    P1->DIR |=   BIT1;
    P1->REN |=   BIT1;
    P1->OUT |=   BIT1;
    P1->IFG &=  ~BIT1; //interrupt flag to be cleared first
    P1->IES |=   BIT1; //high to low
    P1->IE  |=   BIT1 ;
//
////    /* Right button configure */
//    P1->SEL0 &= ~BIT4;
//    P1->SEL1 &= ~BIT4;
//    P1->DIR |=   BIT4;
//    P1->REN |=   BIT4;
//    P1->OUT |=   BIT4;
//    P1->IFG &=  ~BIT4; //interrupt flag to be cleared first
//    P1->IES =   BIT4; //high to low
//    P1->IE  =   BIT4;
//
//    /* Configure Latency Test Output Pin */
//  P1->SEL0 = ???;
//  P1->SEL1 = ???;
//  P1->DIR = ???;
//  P1->OUT = ???;
//
 /* Enable Interrupts in the NVIC */
    NVIC_EnableIRQ( PORT1_IRQn);
}

void PORT1_IRQHandler(){
    uint32_t h = 0;

    P1->OUT ^= BIT0;

    for(h=0; h < 1000; h++);

    //P1->OUT = ~BIT0;

    //PART 4. DEMO TO TA
//    if (P1->IFG == LEFT_INTERRUPT_BUTTON) {
//        // DO STUFF FOR LEFT BUTTON
//        P1->OUT ^= BIT1;
//    }
//    else if(P1->IFG == RIGHT_INTERRUPT_BUTTON){
//        //DO STUFF FOR RIGHT BUTTON
//    }
//    else{
//        //
//    }

    P1->IFG &=  ~BIT1; //clear the flag you jackass

    //toggle the LED
}

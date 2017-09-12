/*
 * port.c
 *
 *  Created on: Sep 10, 2017
 *      Author: kk
 */

// Configure the GPIO
#include "port.h"
#include "msp.h"

void GPIO_configure(void)
{

    /* Configure Led 1 */
    P1->SEL0 &= ~BIT0;
    P1->SEL1 &= ~BIT0;
    P1->DIR |= BIT0;
    P1->OUT |= BIT0;  //on

    testLED1(); //toggle 20 times visual  feedback


//    /* Configure RGB led */
    P2->SEL0 &= ~(BIT0 | BIT1 | BIT2);
    P2->SEL1 &= ~(BIT0 | BIT1 | BIT2);
    P2->DIR  |= (BIT0 | BIT1 | BIT2);
    P2->OUT  &= (BIT0 | BIT1 | BIT2); //HIGH

    testRGB();


//    //data from encoder
//    P1->SEL0 = ???;
//    P1->SEL1 = ???;
//    P1->DIR = ???;
//    P1->REN = ???;
//    P1->OUT = ???;
//    P1->IFG = ???;
//    P1->IES = ???;
//    P1->IE = ???;

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
    P1->DIR &=  ~BIT4;
    P1->REN |=   BIT4;
    P1->OUT |=   BIT4;
    P1->IFG &=  ~BIT4; //interrupt flag to be cleared first
    P1->IES |=   BIT4; //high to low
    P1->IE  |=   BIT4;

//
//    /* Configure Latency Test Output Pin */
//  P1->SEL0 = ???;
//  P1->SEL1 = ???;
//  P1->DIR = ???;
//  P1->OUT = ???;
//
    /* Enable Interrupts in the NVIC */
    NVIC_EnableIRQ(PORT1_IRQn);
}

void PORT1_IRQHandler()
{
    uint32_t h = 0;



    //P1->OUT = ~BIT0;

    //PART 4. DEMO TO TA
 if(P1IFG & BIT1){
        //DO STUFF FOR RIGHT BUTTON
        P1->OUT ^= BIT0;
        for (h = 0; h < 10000; h++)
            P1->IFG &= ~BIT1; //clear the flag you jackass
    }
 else if(P1IFG & BIT4){

     testRGB();
         P1->IFG &= ~BIT4;
 }
    else{
        //
    }

    //toggle the LED
}

void testLED1(){
    //led test red
     uint16_t delays = 0;
     uint8_t test = 0;
     for (test = 0; test < 20; test++)
     {
         P1->OUT ^= BIT0;
         for (delays = 0; delays < 10000; delays++) ;
     }
}

void testRGB(){
    uint8_t color = 0b00000000;
    uint32_t    delays = 0;
    uint8_t index =0;
    for(index =0; index < 8; index ++){
        P2->OUT ^= BIT1|BIT2| BIT3;
   for(delays = 0; delays < 40000; delays++);
    }
   // P2->OUT = 0x0; //clear it!
}

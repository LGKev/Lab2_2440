#include "msp.h"
#include <stdint.h>
#include "timer.h"
#include "port.h"



/*
 * https://e2e.ti.com/support/microcontrollers/msp430/f/166/t/305555
 * */


void main(void)
{

    WDT_A->CTL = WDT_A_CTL_HOLD | WDT_A_CTL_PW;

//    <DISABLE_WATCHDOG>
//
//
//


//  <CONFIGURE_PORTS>
   // GPIO_configure();

//  <CONFIGURE_TIMER>
//  <ENBALE_GLOBAL_INTERRUPTS>
//
    P1->SEL0 = 0x0;//~BIT0;
    P1->SEL1 = 0x0;//~BIT0;
    P1->DIR |= BIT0 ;
    P1->OUT |= BIT0;

    uint16_t delays=0;
    uint8_t test =0;
        for(test =0; test<20; test++){
            P1->OUT ^=BIT0;
            for(delays = 0; delays < 10000; delays++);
        }


    //Start of a test
    //set up left button as input
       //P1->SEL0 = 0x0;//~BIT1;
       //P1->SEL1 = 0x0;//~BIT1; don't negate because ~bit0 is 111110
       P1->DIR |=   ~BIT1; // set as 0 for input
       P1->REN |=   BIT1;
       P1->OUT |=   BIT1;
       P1->IFG &=  ~BIT1; //interrupt flag to be cleared first
       P1->IES =   BIT1; //high to low
       P1->IE  =   BIT1 ;



       NVIC_EnableIRQ( PORT1_IRQn);

       __enable_irq();


    while (1){
//        if(P1->IN == ~BIT1){
//            P1->OUT = BIT0;
//        }
    }
}



//
//void ISR-FUNCTION-TIMER()
//{
//
//}
//
//void timer_a0_config(){
////    TIMER_A0->R = ???;         // Reset count
////    TIMER_A0->CTL = ???;       // SMCLK, Up mode
////    TIMER_A0->CCR[0] = ???;    // Value to count to
////    TIMER_A0->CCTL[0] = ???;   // TACCR0 interrupt enabled
//
//    /* Enable Interrupts in the NVIC */
////      NVIC_EnableIRQ(???);
//}
//

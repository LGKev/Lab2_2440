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

    GPIO_configure();

    __enable_irq();


//  <CONFIGURE_TIMER>




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

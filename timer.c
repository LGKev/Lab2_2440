/*
 * timer.c
 *
 *  Created on: Sep 10, 2017
 *      Author: kk
 */

#include "timer.h"
#include "msp.h"

//void ISR-FUNCTION-TIMER()
//{
//
//}
//
void timer_a0_config(){
    __disable_irq();


    TIMER_A0->R = 0 ;         // Reset count, set to 0 at begining
    TIMER_A0->CTL |= (TIMER_A_CTL_SSEL_OFS + TIMER_A_CTL_TASSEL_2 ) | (TIMER_A_CTL_IE_OFS + TIMER_A_CTL_IE );     //UP MODE, SOURCE SEL SMCLK, INTERRUPT ENABLE
    TIMER_A0->CTL |= TIMER_A_CTL_ID_OFS + (TIMER_A_CTL_ID__8); //DIVIDE BY 1
    TIMER_A0->CTL &= ~(TIMER_A_CTL_IFG ); //(TIMER_A_CTL_IFG_OFS) + ~(TIMER_A_CTL_IFG );//CLEAR ANY FLAGS ,totally worked!!! this was the correct way to negate
    TIMER_A0->CCR[0] = 65500;    // Value to count to, from lab questions
    TIMER_A0->CCTL[0] &= ~BIT0;
    TIMER_A0->CCTL[0] |= TIMER_A_CCTLN_CCIE_OFS + TIMER_A_CCTLN_CCIE ;   // INTERRUPT INABLE CAPTURE COMPARE
    //line 20 might be wrong because i just want the capture compare flag set as 1 to enable that....
    //and the CCIF is if a pending interrupt is there

    //clear the flag
    //  (TIMER_A_CTL_IFG_OFS + TIMER_A_CTL_IFG)  but remember &= ~ bit so thats more likely.


    //question do we use the offsets b/c the overlay just takes us to the right place
    //but within the ctl register we still need offsets to set the correct bit
    //it bit 0 is the flag. so no offset, but cpactre compare is bit 4 so we need 4 bit offset?

    //don't start ticking until eveyrthing set
    TIMER_A0->CTL|=(TIMER_A_CTL_MC_OFS + TIMER_A_CTL_MC__UP );


    /* Enable Interrupts in the NVIC */
      NVIC_EnableIRQ(TA0_0_IRQn);

      //set to compare mode?
//     TIMER_A_CCTLN[0]|= TIMER_A_CCTLN_CM_1;
}

void TA0_0_IRQHandler(){
    //everytime the timer compare capture, this code execcutes

    //P1->OUT ^= BIT0; //blink red led.

   // P1->OUT^=BIT7;


   if(TIMER_A0->CCTL[0] & CCIFG){
       P1->OUT ^= BIT7;
       TIMER_A0->CCTL[0] &= ~CCIFG; //not clearing the ccifg flag..., seen in register, try 1


           P2->OUT += BIT0;
                //i wonder if a simple count would work?
                if(P2->OUT >= 0b11111111){
                        P2->OUT &= ~(BIT0 | BIT1 | BIT2); //clear;
                        P1->OUT ^= BIT7;
                }
   }
//   else
//    if(TIMER_A0->CCTL[1] & CCIFG){
//
//             P2->OUT += BIT0;
//             //i wonder if a simple count would work?
//             if(P2->OUT >= 0b11111111){
//                     P2->OUT &= ~(BIT0 | BIT1 | BIT2); //clear;
//                     P1->OUT ^= BIT7;
//             }
//
//
//   }
   else{
       TIMER_A0->CTL &= ~TIMER_A_CTL_IFG;//moved here b/c i think it was clearing flags too early. only clear 1 flag a time.
   }

}
//
//void sysTickConfig(){
//    SysTick_Config(ticks)
//}

void timer_a0_configTimer1(){
    __disable_irq();
    TIMER_A0->CTL &=TIMER_A_CTL_MC_OFS + ~(TIMER_A_CTL_MC__STOP ); //stopped but also altered clock source... not way to clera.


        TIMER_A0->R = 1 ;         // Reset count, set to 0 at begining
        TIMER_A0->CTL |= (TIMER_A_CTL_SSEL_OFS + TIMER_A_CTL_TASSEL_2 ) | (TIMER_A_CTL_IE_OFS + TIMER_A_CTL_IE );     //UP MODE, SOURCE SEL SMCLK, INTERRUPT ENABLE
        TIMER_A0->CTL |= TIMER_A_CTL_ID_OFS + (TIMER_A_CTL_ID__8); //DIVIDE BY 1
        TIMER_A0->CTL &= ~(TIMER_A_CTL_IFG ); //(TIMER_A_CTL_IFG_OFS) + ~(TIMER_A_CTL_IFG );//CLEAR ANY FLAGS ,totally worked!!! this was the correct way to negate
        TIMER_A0->CCR[1] = 65500;    // Value to count to, from lab questions
        TIMER_A0->CCTL[1] &= ~CCIFG;
        TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_CCIE_OFS + TIMER_A_CCTLN_CCIE ;   // INTERRUPT INABLE CAPTURE COMPARE

        TIMER_A0->CTL|=(TIMER_A_CTL_MC_OFS + TIMER_A_CTL_MC__CONTINUOUS );


            /* Enable Interrupts in the NVIC */
              NVIC_EnableIRQ(TA0_0_IRQn);
}


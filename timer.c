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

    TIMER_A0->R = 0 ;         // Reset count, set to 0 at begining
    TIMER_A0->CTL |= (TIMER_A_CTL_MC_OFS + TIMER_A_CTL_MC__UP )|(TIMER_A_CTL_SSEL_OFS + TIMER_A_CTL_TASSEL_2 ) | (TIMER_A_CTL_IE_OFS + TIMER_A_CTL_IE );     //UP MODE, SOURCE SEL SMCLK, INTERRUPT ENABLE
    TIMER_A0->CTL |= TIMER_A_CTL_ID_OFS + (TIMER_A_CTL_ID_0); //DIVIDE BY 1
    TIMER_A0->CTL &= ~(TIMER_A_CTL_IFG ); //(TIMER_A_CTL_IFG_OFS) + ~(TIMER_A_CTL_IFG );//CLEAR ANY FLAGS ,totally worked!!! this was the correct way to negate
    TIMER_A0->CCR[0] |= 100;    // Value to count to, from lab questions
    TIMER_A0->CCR[1] |= 50;
    TIMER_A0->CCTL[0] &= ~BIT0;
    TIMER_A0->CCTL[0] |= TIMER_A_CCTLN_CCIE_OFS + TIMER_A_CCTLN_CCIE ;   // INTERRUPT INABLE CAPTURE COMPARE
    //line 20 might be wrong because i just want the capture compare flag set as 1 to enable that....
    //and the CCIF is if a pending interrupt is there

    //clear the flag
    //  (TIMER_A_CTL_IFG_OFS + TIMER_A_CTL_IFG)  but remember &= ~ bit so thats more likely.


    //question do we use the offsets b/c the overlay just takes us to the right place
    //but within the ctl register we still need offsets to set the correct bit
    //it bit 0 is the flag. so no offset, but cpactre compare is bit 4 so we need 4 bit offset?

    /* Enable Interrupts in the NVIC */
      NVIC_EnableIRQ(TA0_0_IRQn);

      //set to compare mode?
//     TIMER_A_CCTLN[0]|= TIMER_A_CCTLN_CM_1;
}

void TA0_0_IRQHandler(){
    //everytime the timer compare capture, this code execcutes

    //P1->OUT ^= BIT0; //blink red led.
    P1->OUT ^= BIT7;
//    TIMER_A_CTL[] //CLEAR THE FLG!
    TIMER_A0->CCTL[0] &= ~CCIFG; //not clearing the ccifg flag..., seen in register, try 1
  //  TIMER_A0->CCTL[0]
     //TIMER_A0->CTL &=  ~(TIMER_A_CTL_IFG );//CLEAR ANY FLAGS , did not clear the flag., try 1
  // TIMER_A0->CCTL[0] = 0; //try 2// definitly is touching CCTL[0]
   TIMER_A0->CCTL[0] |=BIT0;//not working iether to flip anything!


}

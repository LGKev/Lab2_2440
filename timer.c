/*
 * timer.c
 *
 *  Created on: Sep 10, 2017
 *      Author: kk
 */

#include "timer.h"
#include "msp.h"

#define DEBUG_ME (2)
#define PROBLEM10 (1)


/* Problem 5a, defines */
//#define TIMER_65000                     (1)
//#define TIMER_40000         (1)
//#define TIMER_20000
#define TIMER_1000

//#define TIMER_EXPANDER


void timer_a0_config(){
    __disable_irq();
#ifdef PROBLEM9
    TIMER_A0->R = 0 ;         // Reset count, set to 0 at begining
    TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2|TIMER_A_CTL_ID__8| TIMER_A_CTL_MC__UP;    //UP MODE, SOURCE SEL SMCLK, INTERRUPT ENABLE

    TIMER_A0->CCR[0] = 4726;    // Value to count to, from lab questions
    TIMER_A0->CCTL[0] &= ~CCIFG; //clear compare captture flag
    TIMER_A0->CCTL[0] |= TIMER_A_CCTLN_CCIE ;   // INTERRUPT INABLE CAPTURE COMPARE
    TIMER_A0->EX0 = TIMER_A_EX0_TAIDEX_7; //divide by 8
#endif


#ifdef PROBLEM10
    TIMER_A0->R = 0 ;         // Reset count, set to 0 at begining
    TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2|TIMER_A_CTL_ID__8| TIMER_A_CTL_MC__UP;    //UP MODE, SOURCE SEL SMCLK, INTERRUPT ENABLE

    TIMER_A0->CCR[0] = 11812;    // Value to count to, from lab questions
    TIMER_A0->CCTL[0] &= ~CCIFG; //clear compare captture flag
    TIMER_A0->CCTL[0] |= TIMER_A_CCTLN_CCIE ;   // INTERRUPT INABLE CAPTURE COMPARE
    TIMER_A0->EX0 = TIMER_A_EX0_TAIDEX_7; //divide by 8
#endif

    /* Enable Interrupts in the NVIC */
      NVIC_EnableIRQ(TA0_0_IRQn);




}




void timer_a0_configTimer1(){
    __disable_irq();



//
//
//
//
//            TIMER_A0->R = 0 ;         // Reset count, set to 0 at begining
//            TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2|TIMER_A_CTL_ID__8|TIMER_A_CTL_MC__UP;// | (TIMER_A_CTL_IE_OFS + TIMER_A_CTL_IE );     //UP MODE, SOURCE SEL SMCLK, INTERRUPT ENABLE
//            TIMER_A0->CCTL[0] &= ~(CCIFG ); //(TIMER_A_CTL_IFG_OFS) + ~(TIMER_A_CTL_IFG );//CLEAR ANY FLAGS ,totally worked!!! this was the correct way to negate
//
//            TIMER_A0->CCR[1] = 65000;    // Value to count to, from lab questions
//
//
//           // TIMER_A0->CCTL[1] = 0; //if we clear everythign at the start this is no longer necessary.
//            TIMER_A0->CCTL[1] = TIMER_A_CCTLN_CCIE ;// | TIMER_A_EX0_TAIDEX_4; //added this at 9:12pm, maybe not capturing!
//                      /* Enable Interrupts in the NVIC */
//
//        //now remeber kids. read the data sheet. cuz the expansion register is its own register. funny
////#ifdef TIMER_EXPANDER
////            TIMER_A0->EX0 = TIMER_A_EX0_TAIDEX_7; //divide by 8
////#endif

            TIMER_A0->R = 0 ;         // Reset count, set to 0 at begining
            TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2|TIMER_A_CTL_ID__1| TIMER_A_CTL_MC__UP;    //UP MODE, SOURCE SEL SMCLK, INTERRUPT ENABLE

            //   TIMER_A0->CTL &= ~(TIMER_A_CTL_IFG );

#ifdef TIMER_65000
               TIMER_A0->CCR[0] = 65000;    // Value to count to, from lab questions
#endif

#ifdef TIMER_40000
               TIMER_A0->CCR[0] = 40000;    // Value to count to, from lab questions
#endif

#ifdef TIMER_20000
               TIMER_A0->CCR[0] = 20000;    // Value to count to, from lab questions
#endif
//#ifdef TIMER_1000
//               TIMER_A0->CCR[0] = 1000;    // Value to count to, from lab questions
//#endif

               TIMER_A0->CCR[1] = 1000;    // Value to count to, from lab questions


               TIMER_A0->CCTL[1] &= ~CCIFG; //clear compare captture flag
               TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_CCIE ;   // INTERRUPT INABLE CAPTURE COMPARE





              NVIC_EnableIRQ(TA0_N_IRQn);
}


void TA0_0_IRQHandler(){
    //everytime the timer compare capture, this code execcutes

    //P1->OUT ^= BIT0; //blink red led.
//idk google it
    //cctl[1] has its own section!!!! jfc.

    if(TIMER_A0->CCTL[0] & CCIFG){ //had cct[1] here and so thats why it was working. incorrect amazing how much can be wrong AND STILL WORK.

        P1->OUT^=BIT7;
//             P2->OUT += BIT0; //shift instead of add!! <<
//             //i wonder if a simple count would work?
//             if(P2->OUT >= 0b11111111){
//                     P2->OUT &= ~(BIT0 | BIT1 | BIT2); //clear;
//                     P1->OUT ^= BIT7;
//             }


   }


       TIMER_A0->CTL &= ~TIMER_A_CTL_IFG;//moved here b/c i think it was clearing flags too early. only clear 1 flag a time.
       TIMER_A0->CCTL[0] &= ~CCIFG;


}

//so this is the hanlder we need, but unforunately my flag isn't set still!
void TA0_N_IRQHandler(){ //dedicated for 1-5? and so i guess Ta_0_0 is the handler specifically for cctl[0]
    P1->OUT ^= BIT7;


    if(TIMER_A0->CCTL[1] & CCIFG){ //ABSOLUTELY necessary will not work otherwise.

        P1->OUT ^= BIT7;
        P1->OUT ^=BIT0;

    }

    TIMER_A0->CTL &= ~TIMER_A_CTL_IFG;//moved here b/c i think it was clearing flags too early. only clear 1 flag a time.

    TIMER_A0->CCTL[1] &= ~CCIFG;

}

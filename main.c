#include "msp.h"
#include <stdint.h>
#include "timer.h"
#include "port.h"



/*
 * https://e2e.ti.com/support/microcontrollers/msp430/f/166/t/305555
 * */



//volatile  uint8_t hissa;

void main(void)



{

//    hissa =20;
    uint32_t test =54;
    WDT_A->CTL = WDT_A_CTL_HOLD | WDT_A_CTL_PW;

    GPIO_configure();

 // timer_a0_config();

   timer_a0_configTimer1();

    __enable_irq();

//    while(1){
//    //rgbCycle();
//    }



//  <CONFIGURE_TIMER>


    while (1){
//        if(P1->IN == ~BIT1){
//            P1->OUT = BIT0;
//        }
      //  TIMER_A0->CCTL[1] |= CCIFG;
        //P1->OUT ^= BIT7;
      //  P1->OUT ^= BIT7;
    }
}




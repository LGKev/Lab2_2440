#include "msp.h"
#include <stdint.h>
#include "timer.h"
#include "port.h"

#define TIMER_0 (1)


/*
 * https://e2e.ti.com/support/microcontrollers/msp430/f/166/t/305555
 * */



//volatile  uint8_t hissa;
volatile uint32_t count = 0;

void main(void)
{

//    hissa =20;
    uint32_t test =54;
    WDT_A->CTL = WDT_A_CTL_HOLD | WDT_A_CTL_PW;

  GPIO_configure();
// timer_a0_config();

 // timer_a0_configTimer1();

    __enable_irq();



    encoderInterruptConfig();


    while (1){
       // P1->OUT |= BIT7;//HIGH
//        if(count == 40000){
//            uint32_t stop =0;
//            P2->OUT &=~BIT2;
//            P2->OUT |=BIT2;
//            for(stop = 0; stop < 300000; stop++);
//            P2->OUT &=~BIT2;
//
//                count =0;
//        }
       // P1->IFG |= 1;
    }
}




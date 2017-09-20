#include "msp.h"
#include <stdint.h>
#include "timer.h"
#include "port.h"

#define TIMER_0
#define SYS_TICK_MEASUREMENT
#define ENCODER_TEST

#define N_ROTATIONS_INTERRUPT // lights led when N rotations have been triggered (14*5 = 70 interrupts)
#define N_INTERRUPTS        (70) //problem

//#define LATENCY_TEST
//#define GLOBAL_COUNT_TEST // checks to see global variable works


/*
 * https://e2e.ti.com/support/microcontrollers/msp430/f/166/t/305555
 * */



volatile uint32_t count = 0;
volatile uint32_t currentVal = 21;
volatile uint32_t currentVal2 = 53;

void main(void)
{

//    hissa =20;
    uint32_t test =54;
    WDT_A->CTL = WDT_A_CTL_HOLD | WDT_A_CTL_PW;

  GPIO_configure();
// timer_a0_config();

 // timer_a0_configTimer1();


#ifdef SYS_TICK_MEASUREMENT
  SysTick_Config(1000000000);// 1 billi
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Pos | SysTick_CTRL_ENABLE_Msk;

  SysTick->LOAD = 535353;
#endif
    __enable_irq();

    currentVal = SysTick->VAL;
#ifdef ENCODER_TEST
    encoderInterruptConfig();
#endif

#ifdef LATENCY_TEST
    while (1){
        P1->OUT |= BIT7;//HIGH
        P1->IFG |= 1;
    }
#endif

#ifdef GLOBAL_COUNT_test
    while(1){
                if(count == 40000){
                    uint32_t stop =0;
                    P2->OUT &=~BIT2;
                    P2->OUT |=BIT2;
                    for(stop = 0; stop < 300000; stop++);
                    P2->OUT &=~BIT2;

                        count =0;
                }
    }
#endif

#ifdef N_ROTATIONS_INTERRUPT
    if(count == N_INTERRUPTS ){
        uint32_t stop = 0;
        P2->OUT &= ~BIT2;
        P2->OUT |= BIT2;
        for (stop = 0; stop < 300000; stop++);
        //figure out a way to use the timer to flip the bit with a semiphore
        P2->OUT &= ~BIT2;

        count = 0;
    }

#endif

}




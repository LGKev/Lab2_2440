#include "msp.h"
#include <stdint.h>
#include "timer.h"
#include "port.h"
#include "demoDefines.h"





/*====================================================================================
 * Additional Tests Not for Demo
 * ====================================================================================
 */
//#define LATENCY_TEST //Problem 3


/*
 * https://e2e.ti.com/support/microcontrollers/msp430/f/166/t/305555
 * */



volatile uint32_t count = 0;
volatile uint32_t currentVal = 21;
volatile uint32_t currentVal2 = 53;
volatile uint32_t totalCount = 0; //count for the lifetime of the controller.
float distanceCalculator(uint32_t totalCount);



void main(void)
{


    WDT_A->CTL = WDT_A_CTL_HOLD | WDT_A_CTL_PW;

  GPIO_configure();

#ifdef TIMER_A_CCR0
  timer_a0_config();
#endif

#ifdef TIMER_A_CCR1
 timer_a0_configTimer1();
#endif

#ifdef SYS_TICK_MEASUREMENT
  SysTick_Config(1000000000);// 1 billi
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Pos | SysTick_CTRL_ENABLE_Msk;

  SysTick->LOAD = 535353;

  currentVal = SysTick->VAL;

#endif

#ifdef ENCODER_CONFIG
    encoderInterruptConfig();
#endif

#ifdef LATENCY_TEST
    while (1){
        P1->OUT |= BIT7;//HIGH
        P1->IFG |= 1;
    }
#endif

#ifdef N_ROTATIONS_INTERRUPT
    while(1){
    if(count == N_INTERRUPTS ){
        uint32_t stop = 0;
        P2->OUT &= ~BIT2;
        P2->OUT |= BIT2;// blue on
        for (stop = 0; stop < 9000; stop++);
        //figure out a way to use the timer to flip the bit with a semiphore
        P2->OUT &= ~BIT2;
        count = 0;
    }
  }
#endif

#ifdef CALCULATE_DISTANCE
    float distance = distanceCalculator(totalCount);
#endif


    __enable_irq();

    while(1);

}

/*
 * This function takes in the number of interrupts triggered
 * and determines the distance traveled.
 *
 * We only care about major distances and should only incriment after a wheel rotation.
 * For better accuracy, the frequency of the calculation can be increased. For now
 * distance is only calculated after 1 wheel rotation, thus we know the distance within .31415
 * of a meter.
 * */
#ifdef CALCULATE_DISTANCE
    float distanceCalculator(uint32_t totalCount){
        float distanceTraveled = 0;
        distanceTraveled = totalCount * count;
        return distanceTraveled;
    }
#endif

#include "msp.h"
#include <stdint.h>
#include "timer.h"
#include "port.h"

//#TIMER_0 (1)


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

  //timer_a0_config();

  timer_a0_configTimer1();

    __enable_irq();







    while (1){
    }
}




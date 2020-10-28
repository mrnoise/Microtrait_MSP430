#include "Examples/WDT.hpp"

#include "driverlib/MSP430FR5xx_6xx/driverlib.h"

#define GPIO_PORT_LED1 GPIO_PORT_P1
#define GPIO_PIN_LED1  GPIO_PIN0
#define GPIO_PORT_LED2 GPIO_PORT_P1
#define GPIO_PIN_LED2  GPIO_PIN1
#define GPIO_PORT_S1   GPIO_PORT_P2
#define GPIO_PIN_S1    GPIO_PIN3
#define GPIO_PORT_S2   GPIO_PORT_P2
#define GPIO_PIN_S2    GPIO_PIN7

void runWdtExample() {
    //Initialize WDT module in timer interval mode,
    //with SMCLK as source at an interval of 32 ms.
    WDT_A_initIntervalTimer(WDT_A_BASE,
        WDT_A_CLOCKSOURCE_SMCLK,
        WDT_A_CLOCKDIVIDER_32K);

    WDT_A_start(WDT_A_BASE);

    //Enable Watchdog Interupt
    SFR_clearInterrupt(SFR_WATCHDOG_INTERVAL_TIMER_INTERRUPT);
    SFR_enableInterrupt(SFR_WATCHDOG_INTERVAL_TIMER_INTERRUPT);

    //Set LED1 to output direction
    GPIO_setAsOutputPin(
        GPIO_PORT_LED1,
        GPIO_PIN_LED1);

    PMM_unlockLPM5();

    //Enter LPM0, enable interrupts
    __bis_SR_register(LPM0_bits + GIE);
    //For debugger
    __no_operation();
}


//Watchdog Timer interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = WDT_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(WDT_VECTOR)))
#endif
    void
    WDT_A_ISR(void) {
    //Toggle LED1
    GPIO_toggleOutputOnPin(
        GPIO_PORT_LED1,
        GPIO_PIN_LED1);
}

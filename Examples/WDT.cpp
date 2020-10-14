#include "Examples/WDT.hpp"

#include <msp430.h>


void runWdtExample() {
    WDTCTL = WDT_MDLY_32;// WDT 32ms, SMCLK, interval timer

    P1OUT &= ~BIT0;// Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT0; // Set P1.0 to output direction

    PM5CTL0 &= ~LOCKLPM5;// Disable the GPIO power-on default high-impedance mode
                         // to activate previously configured port settings

    SFRIE1 |= WDTIE;// Enable WDT interrupt

    __bis_SR_register(LPM0_bits | GIE);// Enter LPM0, enable interrupts
    __no_operation();                  // For debug
}


// Watchdog Timer interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(WDT_VECTOR))) WDT_ISR(void)
#else
#error Compiler not supported!
#endif
{
    P1OUT ^= BIT0;// Toggle P1.0 (LED)
}

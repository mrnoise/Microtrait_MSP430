#include "TimerA.hpp"
#include <msp430.h>

#define COMPARE_VALUE 50000

void runTimerAExample() {

    WDTCTL = WDTPW | WDTHOLD;// Stop WDT

    // Configure GPIO
    P1DIR |= BIT0;// P1.0 output
    P1OUT |= BIT0;// P1.0 high

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    TA0CCTL0 |= CCIE;// TACCR0 interrupt enabled
    TA0CCR0 = COMPARE_VALUE;
    TA0CTL |= TASSEL__SMCLK | MC__CONTINUOUS;// SMCLK, continuous mode

    __bis_SR_register(LPM0_bits | GIE);// Enter LPM3 w/ interrupts
    __no_operation();                  // For debug
}


// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(TIMER0_A0_VECTOR))) Timer_A(void)
#else
#error Compiler not supported!
#endif
{
    P1OUT ^= BIT0;
    TA0CCR0 += COMPARE_VALUE;// Add Offset to TACCR0
}

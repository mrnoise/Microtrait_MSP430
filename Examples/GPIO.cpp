#include "Examples/GPIO.hpp"

#include <msp430.h>

void runGpioExample() {
    WDTCTL = WDTPW | WDTHOLD;
    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Configure GPIO
    P1OUT &= ~BIT0;// Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT0; // Set P1.0 to output direction

    P2OUT |= BIT3; // Configure P2.3 as pulled-up
    P2REN |= BIT3; // P2.3 pull-up register enable
    P2IES |= BIT3; // P2.3 Hi/Low edge
    P2IE |= BIT3;  // P2.3 interrupt enabled
    P2IFG &= ~BIT3;// P2.3 IFG cleared

    P1OUT |= BIT4; // Configure P1.4 as pulled-up
    P1REN |= BIT4; // P1.4 pull-up register enable
    P1IES |= BIT4; // P1.4 Hi/Low edge
    P1IE |= BIT4;  // P1.4 interrupt enabled
    P1IFG &= ~BIT4;// P1.4 IFG cleared

    __bis_SR_register(GIE);
}


// Port 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT1_VECTOR))) Port_1(void)
#else
#error Compiler not supported!
#endif
{
    P1IFG &= ~BIT4;// Clear P1.3 IFG
    P1OUT ^= BIT0;
}

// Port 2 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT2_VECTOR))) Port_2(void)
#else
#error Compiler not supported!
#endif
{
    P2IFG &= ~BIT3;// Clear P1.3 IFG
    P1OUT ^= BIT0;
}

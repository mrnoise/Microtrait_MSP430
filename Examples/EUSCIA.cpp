#include "Examples/EUSCIA.hpp"
#include <msp430.h>
#include <stdint.h>

#define CHECKBYTE 123

void runEusciAExample() {
    // stop watchdog
    WDTCTL = WDTPW | WDTHOLD;

    // Configure GPIO
    P1OUT &= ~BIT0;       // Clear P1.0 output latch
    P1DIR |= BIT0;        // For LED on P1.0
    P3SEL0 |= BIT4 | BIT5;// Configure UART pins
    P3SEL1 &= ~(BIT4 | BIT5);

    PM5CTL0 &= ~LOCKLPM5;

    // Configure USCI_A0 for UART mode
    UCA1CTL1 |= UCSWRST;
    UCA1CTL1 = UCSSEL__SMCLK;//
    UCA1BRW  = 6;            // 9600 baud
    UCA1MCTLW |= 0x5300;     // 1E6/9600 - INT(1E6/9600)=0.41

    UCA1CTL1 &= ~UCSWRST;// release from reset
    UCA1IFG &= ~UCRXIFG; // Clear USCI_A0 RX interrupt
    UCA1IE |= UCRXIE;    // Enable USCI_A0 RX interrupt

    __enable_interrupt();

    while (1) {
        // Load data onto buffer
        UCA1TXBUF = CHECKBYTE;
        __bis_SR_register(LPM0_bits | GIE);// Enter LPM0, interrupts enabled
    }
}


#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_A1_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_A1_VECTOR)))
#endif
    void
    USCI_A1_ISR(void) {
    switch (__even_in_range(UCA1IV, USCI_UART_UCTXCPTIFG)) {
        case USCI_NONE: break;
        case USCI_UART_UCRXIFG: {
            const uint8_t rx = UCA1RXBUF;
            if (rx != CHECKBYTE)// Check value
            {
                P1OUT |= BIT0;// If incorrect turn on P1.0
                while (1)
                    ;
            }
        } break;
        case USCI_UART_UCTXIFG: break;
        case USCI_UART_UCSTTIFG: break;
        case USCI_UART_UCTXCPTIFG: break;
    }

    __bic_SR_register_on_exit(CPUOFF);// Exit LPM0 on reti
}

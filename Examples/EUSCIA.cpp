#include "Examples/EUSCIA.hpp"
#include "driverlib/MSP430FR5xx_6xx/driverlib.h"

#define CHECKBYTE 123

void runEusciAExample() {
    // stop watchdog
    WDT_A_hold(WDT_A_BASE);

    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P3,
        GPIO_PIN4 + GPIO_PIN5,
        GPIO_PRIMARY_MODULE_FUNCTION);

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    PMM_unlockLPM5();

    EUSCI_A_UART_initParam param;
    param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK;
    param.clockPrescalar    = 6;
    param.firstModReg       = 8;
    param.secondModReg      = 17;
    param.parity            = EUSCI_A_UART_NO_PARITY;
    param.msborLsbFirst     = EUSCI_A_UART_LSB_FIRST;
    param.numberofStopBits  = EUSCI_A_UART_ONE_STOP_BIT;
    param.uartMode          = EUSCI_A_UART_MODE;
    param.overSampling      = EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION;
    EUSCI_A_UART_init(EUSCI_A1_BASE, &param);

    EUSCI_A_UART_enable(EUSCI_A1_BASE);
    EUSCI_A_UART_clearInterrupt(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    EUSCI_A_UART_enableInterrupt(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);

    __enable_interrupt();

    while (1) {
        //TXData = TXData + 1;// Increment TX data
        // Load data onto buffer
        EUSCI_A_UART_transmitData(EUSCI_A1_BASE, CHECKBYTE);
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
            const uint8_t rx = EUSCI_A_UART_receiveData(EUSCI_A1_BASE);
            if (rx != CHECKBYTE)// Check value
            {
                GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
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

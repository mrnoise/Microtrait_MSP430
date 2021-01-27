#include "EUSCIA.hpp"
#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

static constexpr uint8_t c_checkByte = 123;

void runEusciAExample() {

    WdtA wdt{};
    wdt.hold();

    GPIO::Port3 p3;
    p3.setAsPeripheralModuleFunctionInputPin(GPIO::MODULE_FUNC::PRIMARY, GPIO::PIN::P4 | GPIO::PIN::P5);

    GPIO::Port1 p1;
    p1.setAsOutputPin(GPIO::PIN::P0);
    p1.setOutputLowOnPin(GPIO::PIN::P0);

    Pmm pmm{};
    pmm.unlockLPM5();

    constexpr EUSCIA::UART::initParam param{
        // Baudrate 9600 at 1MHz SMCLCK
        EUSCIA::UART::CLOCKSOURCE::SMCLK,
        6,
        8,
        17,
        EUSCIA::UART::PARITY::NO,
        EUSCIA::UART::ENDIAN::LSB_FIRST,
        EUSCIA::UART::STOPBIT::ONE,
        EUSCIA::UART::MODE::UART,
        EUSCIA::UART::BAUD_GENERATION::OVERSAMPLING
    };

    EUSCIA::UART::A1 a1;
    a1.init(param);
    a1.enable();
    a1.clearInterrupt(EUSCIA::UART::INT::RECEIVE);
    a1.enableInterrupt(EUSCIA::UART::INT::RECEIVE, EUSCIA::UART::INT_EXT::NONE);

    while (1) {
        // Load data onto buffer
        a1.transmitData(c_checkByte);
        __bis_SR_register(LPM0_bits | GIE);// Enter LPM0, interrupts enabled
    }
};


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
            EUSCIA::UART::A1 a1;
            const uint8_t    rx = a1.receiveData();
            if (rx != c_checkByte)// Check value
            {
                GPIO::Port1 p1;
                p1.setOutputHighOnPin(GPIO::PIN::P0);

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

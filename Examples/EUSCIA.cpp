#include "EUSCIA.hpp"
#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

void runEusciAExample() {

    WdtA wdt{};
    wdt.hold();

    EUSCIA::UART::initParam param{
        // Baudrate 9600 at 1MHz SMCLCK
        EUSCIA::UART::CLOCKSOURCE::SMCLK,
        6,
        8,
        17,
        EUSCIA::UART::PARITY::NO,
        EUSCIA::UART::ENDIAN::MSB_FIRST,
        EUSCIA::UART::STOPBIT::ONE,
        EUSCIA::UART::MODE::UART,
        EUSCIA::UART::BAUD_GENERATION::OVERSAMPLING
    };

    EUSCIA::UART::A0 a0;
    a0.init(param);


    //Enter LPM0, enable interrupts
    __bis_SR_register(LPM0_bits + GIE);
};

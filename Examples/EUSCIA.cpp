#include "EUSCIA.hpp"
#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

void runEusciAExample() {

    WdtA wdt{};
    wdt.hold();


    //Enter LPM0, enable interrupts
    __bis_SR_register(LPM0_bits + GIE);
};

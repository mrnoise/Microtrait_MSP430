
#include <msp430.h>

//#define RUN_TESTS

#include <stdint.h>
#include "MicroTrait/MSP430/GPIO/PortRegister.hpp"
#include "MicroTrait/Misc/EnumBits.hpp"
#include "MicroTrait/Universal/Register.hpp"
#ifdef RUN_TESTS
#include "MicroTrait/Tests/TestRunner.hpp"
#endif

using namespace MT::MSP430;

int main(void) {
    MT::Universal::Register<&WDTCTL>  wdt{};
    MT::Universal::Register<&PM5CTL0> pm5ctl{};
    wdt.override(WDTPW | WDTHOLD);
    pm5ctl.clear(LOCKLPM5);

#ifdef RUN_TESTS
    MT::Tests::run();
#endif

    GPIO::Port1 p1{};
    GPIO::Port2 p2{};
    GPIO::Port1 p3{};
    p1.setOutputLowOnPin(PIN::P0);
    p1.setAsOutputPin(PIN::P0);

    p2.setAsInputPinWithPullUp(PIN::P3);
    p2.selectInterruptEdge(INT_EDGE::HIGH_TO_LOW, PIN::P3);
    p2.enableInterrupt(PIN::P3);
    p2.clearInterrupt(PIN::P3);

    __bis_SR_register(GIE);


    while (1) {
    }
}

// Port 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT2_VECTOR))) Port_2(void)
#else
#error Compiler not supported!
#endif
{
    GPIO::Port1 p1{};
    GPIO::Port2 p2{};
    p2.clearInterrupt(PIN::P3);
    p1.toggleOutputOnPin(PIN::P0);
}

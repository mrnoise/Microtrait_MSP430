#include "Examples/GPIO.hpp"
#include "Examples/WDTA.hpp"
#include "Examples/TIMERA.hpp"
#include "Examples/EUSCIA.hpp"

#ifdef RUN_TESTS
#include "MicroTrait/MT.hpp"
#include "MicroTrait/Tests/TestRunner.hpp"
using namespace MT::MSP430;
#endif


int main(void) {

#ifdef RUN_TESTS
    WdtA wdt{};
    wdt.hold();

    Pmm pmm{};
    pmm.unlockLPM5();

    MT::Tests::run();

    GPIO::Port1 p1{};
    p1.setOutputHighOnPin(GPIO::PIN::P0);
    p1.setAsOutputPin(GPIO::PIN::P0);
#else
    //Toggels P1.0 in Interrupt of P1.1 or P2.4
    //runGpioExample();

    //Toggels P1.0 in wdt intervall timer interrupt
    //runWdtExample();

    //Toggels P1.0 in TimerA CCR0 interrupt
    //runTimerAExample();

    //UART Ping Pong between RX and TX
    runEusciAExample();
#endif


    while (1) {
    }
}

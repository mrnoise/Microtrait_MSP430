#include "Examples/Settings.hpp"

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

#ifdef EXAMPLE_RUN_GPIO
    //Toggels P1.0 in Interrupt of P1.1 or P2.4
    runGpioExample();
#endif

#ifdef EXAMPLE_RUN_WDTA
    //Toggels P1.0 in wdt intervall timer interrupt
    runWdtExample();
#endif

#ifdef EXAMPLE_RUN_TIMERA
    //Toggels P1.0 in TimerA CCR0 interrupt
    runTimerAExample();
#endif

#ifdef EXAMPLE_RUN_EUSCIA
    //UART Ping Pong between RX and TX
    runEusciAExample();
#endif

#endif

    while (1) {
    }
}

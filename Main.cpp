
//#define RUN_TESTS

#include "Examples/GPIO.hpp"
#include "Examples/WDT.hpp"

#ifdef RUN_TESTS
#include "MicroTrait/Tests/TestRunner.hpp"
#endif


int main(void) {

#ifdef RUN_TESTS
    MT::Tests::run();
#endif

    //Toggels P1.0 by each press of P2.3 in Interrupt
    //runGpioExample();

    //Toggels P1.0 in wdt intervall timer interrupt
    runWdtExample();

    while (1) {
    }
}

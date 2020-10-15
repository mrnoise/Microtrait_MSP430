
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

    //Toggels P1.0 in Interrupt of P2.3 or P1.4
    runGpioExample();

    //Toggels P1.0 in wdt intervall timer interrupt
    //runWdtExample();

    while (1) {
    }
}

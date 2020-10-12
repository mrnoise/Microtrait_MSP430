
//#define RUN_TESTS

#include <stdint.h>
#include "Examples/GPIO.hpp"

#ifdef RUN_TESTS
#include "MicroTrait/Tests/TestRunner.hpp"
#endif


int main(void) {

#ifdef RUN_TESTS
    MT::Tests::run();
#endif

    //Toggels P1.0 by each press of P2.3 in Interrupt
    runGpioExample();

    while (1) {
    }
}

#include "Examples/GPIO.hpp"
#include "Examples/WDT.hpp"


int main(void) {

    //Toggels P1.0 by each press of P2.3 in Interrupt
    //runGpioExample();

    //Toggels P1.0 in wdt intervall timer interrupt
    runWdtExample();

    while (1) {
    }
}

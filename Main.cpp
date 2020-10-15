#include "Examples/GPIO.hpp"
#include "Examples/WDT.hpp"


int main(void) {

    //Toggels P1.0 in interrupt of P2.3 or P1.4
    runGpioExample();

    //Toggels P1.0 in wdt intervall timer interrupt
    //runWdtExample();

    while (1) {
    }
}

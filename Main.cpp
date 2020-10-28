#include "Examples/GPIO.hpp"
#include "Examples/WDT.hpp"
#include "Examples/TimerA.hpp"

int main(void) {

    //Toggels P1.0 in interrupt of P2.4 or P1.1
    //runGpioExample();

    //Toggels P1.0 in wdt intervall timer interrupt
    //runWdtExample();

    //Toggels P1.0 in Timer A interrupt
    runTimerAExample();

    while (1) {
    }
}

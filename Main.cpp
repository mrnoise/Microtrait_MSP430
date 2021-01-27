#include "Examples/GPIO.hpp"
#include "Examples/WDT.hpp"
#include "Examples/TimerA.hpp"
#include "Examples/EUSCIA.hpp"

int main(void) {

    //Toggels P1.0 in interrupt of P2.4 or P1.1
    //runGpioExample();

    //Toggels P1.0 in wdt intervall timer interrupt
    //runWdtExample();

    //Toggels P1.0 in Timer A interrupt
    //runTimerAExample();

    //UART Ping Pong between RX and TX
    runEusciAExample();

    while (1) {
    }
}

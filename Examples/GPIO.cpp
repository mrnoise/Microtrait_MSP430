#include "GPIO.hpp"
#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;


void runGpioExample() {

    WdtA wdt{};
    wdt.hold();

    Pmm pmm{};
    pmm.unlockLPM5();

#ifndef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

    GPIO::Interrupt::Port1 int1;
    int1.registerCallback([](GPIO::PIN pin) {
        if (pin == GPIO::PIN::P1) {
            GPIO::Port1 p1{};
            p1.toggleOutputOnPin(GPIO::PIN::P0);
        }
    });

    GPIO::Interrupt::Port2 int2;
    int2.registerCallback([](GPIO::PIN pin) {
        if (pin == GPIO::PIN::P4) {
            GPIO::Port1 p1{};
            p1.toggleOutputOnPin(GPIO::PIN::P0);
        }
    });

#endif

#ifdef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

    GPIO::Interrupt::Port1 int1{
        [](GPIO::PIN pin) {
            if (pin == GPIO::PIN::P1) {
                GPIO::Port1 p1{};
                p1.toggleOutputOnPin(GPIO::PIN::P0);
            }
        }
    };

    GPIO::Interrupt::Port2 int2{
        [](GPIO::PIN pin) {
            if (pin == GPIO::PIN::P4) {
                GPIO::Port1 p1{};
                p1.toggleOutputOnPin(GPIO::PIN::P0);
            }
        }
    };

#endif

    GPIO::Port1 p1{};
    GPIO::Port2 p2{};
    p1.setOutputLowOnPin(GPIO::PIN::P0);
    p1.setAsOutputPin(GPIO::PIN::P0);

    p2.setAsInputPinWithPullUp(GPIO::PIN::P4);
    p2.selectInterruptEdge(GPIO::INT_EDGE::HIGH_TO_LOW, GPIO::PIN::P4);
    p2.enableInterrupt(GPIO::PIN::P4);
    p2.clearInterrupt(GPIO::PIN::P4);

    p1.setAsInputPinWithPullUp(GPIO::PIN::P1);
    p1.selectInterruptEdge(GPIO::INT_EDGE::HIGH_TO_LOW, GPIO::PIN::P1);
    p1.enableInterrupt(GPIO::PIN::P1);
    p1.clearInterrupt(GPIO::PIN::P1);

    __bis_SR_register(GIE);
}

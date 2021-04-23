#include "Examples/Settings.hpp"
#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

void runGpioExample() {

#ifdef EXAMPLE_RUN_GPIO

    WdtA().hold();
    Pmm().unlockLPM5();

#ifdef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

    constexpr static GPIO::Interrupt::Port1 int1{
        []([[maybe_unused]] const GPIO::PIN pin) {
            GPIO::Port1().toggleOutputOnPin(GPIO::PIN::P0);
        }
    };

    constexpr static GPIO::Interrupt::Port2 int2{
        []([[maybe_unused]] const GPIO::PIN pin) {
            GPIO::Port1().toggleOutputOnPin(GPIO::PIN::P0);
        }
    };

#else

    GPIO::Interrupt::Port1 int1;
    int1.registerCallback([]([[maybe_unused]] const GPIO::PIN pin) {
        GPIO::Port1().toggleOutputOnPin(GPIO::PIN::P0);
    });

    GPIO::Interrupt::Port2 int2;
    int2.registerCallback([]([[maybe_unused]] const GPIO::PIN pin) {
        GPIO::Port1().toggleOutputOnPin(GPIO::PIN::P0);
    });

#endif

    GPIO::Port1 p1{};
    p1.setOutputLowOnPin(GPIO::PIN::P0);
    p1.setAsOutputPin(GPIO::PIN::P0);

    p1.setAsInputPinWithPullUp(GPIO::PIN::P1);
    p1.selectInterruptEdge(GPIO::INT_EDGE::HIGH_TO_LOW, GPIO::PIN::P1);
    p1.enableInterrupt(GPIO::PIN::P1);
    p1.clearInterrupt(GPIO::PIN::P1);

    GPIO::Port2 p2{};
    p2.setAsInputPinWithPullUp(GPIO::PIN::P4);
    p2.selectInterruptEdge(GPIO::INT_EDGE::HIGH_TO_LOW, GPIO::PIN::P4);
    p2.enableInterrupt(GPIO::PIN::P4);
    p2.clearInterrupt(GPIO::PIN::P4);

    __bis_SR_register(GIE);

#endif
}

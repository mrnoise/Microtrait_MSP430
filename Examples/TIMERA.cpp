#include "GPIO.hpp"
#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

#define COMPARE_VALUE 50000

void runTimerAExample() {

    WdtA wdt{};
    wdt.hold();

    GPIO::Port1 p1{};
    p1.setAsOutputPin(GPIO::PIN::P0);
    p1.setOutputHighOnPin(GPIO::PIN::P0);

    Pmm pmm{};
    pmm.unlockLPM5();


#ifndef MT_MSP430_USE_TIMERA_COMPILE_TIME_CALLBACKS

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

#ifdef MT_MSP430_USE_TIMERA_COMPILE_TIME_CALLBACKS
    TIMERA::Interrupt::TA0 int0{
        [](TIMERA::Interrupt::SOURCE src) {
            if (src == TIMERA::Interrupt::SOURCE::REGISTER0) {
                GPIO::Port1 p1{};
                p1.toggleOutputOnPin(GPIO::PIN::P0);

                TIMERA::TA0 ta0;
                ta0.setCompareValue(TIMERA::CAPTURE_COMPARE::REGISTER0, COMPARE_VALUE);
            }
        }
    };
#endif

    TIMERA::TA0 ta0;

    constexpr TIMERA::initContinuous param{
        TIMERA::CLOCKSOURCE::SMCLK,
        TIMERA::CLOCK_DIV::DIV1,
        TIMERA::TAIE_INT::DISABLE,
        TIMERA::CLEAR_COUNT_DIR::ENABLE,
        true
    };

    constexpr TIMERA::initCompare paramCom{
        TIMERA::CAPTURE_COMPARE::REGISTER0,
        TIMERA::CAPTURE_COMPARE_INT::ENABLE,
        TIMERA::COMPARE_OUTPUT::BITVALUE,
        COMPARE_VALUE
    };


    ta0.clearCaptureCompareInterrupt(TIMERA::CAPTURE_COMPARE::REGISTER0);
    ta0.initCompareMode(paramCom);
    ta0.initContinuousMode(param);

    //Enter LPM0, enable interrupts
    __bis_SR_register(LPM0_bits + GIE);

    //For debugger
    __no_operation();
}

#include "GPIO.hpp"
#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

void runTimerAExample() {

    WdtA wdt{};
    wdt.hold();

    Pmm pmm{};
    pmm.unlockLPM5();

    TIMERA::TA0 ta0;

    constexpr TIMERA::initContinuous param{
        TIMERA::CLOCKSOURCE::SMCLK,
        TIMERA::CLOCK_DIV::DIV1,
        TIMERA::GLOBAL_INT::DISABLE,
        TIMERA::CLEAR_COUNT_DIR::ENABLE,
        false
    };

    ta0.initContinuousMode(param);
}

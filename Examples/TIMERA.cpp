#include "Examples/Settings.hpp"
#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

#ifdef EXAMPLE_RUN_TIMERA
static constexpr uint16_t c_compareValue = 50000;
#endif

void runTimerAExample() {

#ifdef EXAMPLE_RUN_TIMERA

    WdtA wdt{};
    wdt.hold();

    GPIO::Port1 p1{};
    p1.setAsOutputPin(GPIO::PIN::P0);
    p1.setOutputHighOnPin(GPIO::PIN::P0);

    Pmm pmm{};
    pmm.unlockLPM5();

#ifdef MT_MSP430_USE_TIMERA_COMPILE_TIME_CALLBACKS
    constexpr static TIMERA::Interrupt::TA0 int0{
        [](const TIMERA::Interrupt::SOURCE src) {
            if (src == TIMERA::Interrupt::SOURCE::REGISTER0) {
                GPIO::Port1 p1{};
                p1.toggleOutputOnPin(GPIO::PIN::P0);

                TIMERA::TA0 ta0;
                ta0.setCompareValue(TIMERA::CAPTURE_COMPARE::REGISTER0, c_compareValue);
            }
        }
    };

#else

    TIMERA::Interrupt::TA0 int0;
    int0.registerCallback(
        [](const TIMERA::Interrupt::SOURCE src) {
            if (src == TIMERA::Interrupt::SOURCE::REGISTER0) {
                GPIO::Port1 p1{};
                p1.toggleOutputOnPin(GPIO::PIN::P0);

                TIMERA::TA0 ta0;
                ta0.setCompareValue(TIMERA::CAPTURE_COMPARE::REGISTER0, c_compareValue);
            }
        });
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
        c_compareValue
    };


    ta0.clearCaptureCompareInterrupt(TIMERA::CAPTURE_COMPARE::REGISTER0);
    ta0.initCompareMode(paramCom);
    ta0.initContinuousMode(param);

    //Enter LPM0, enable interrupts
    __bis_SR_register(LPM0_bits + GIE);
#endif
}

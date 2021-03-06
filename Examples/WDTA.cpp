#include "Examples/Settings.hpp"
#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

void runWdtExample() {

#ifdef EXAMPLE_RUN_WDTA

    WdtA().startIntervalTimer(WDTA::CLOCKSOURCE::SMCLK, WDTA::CLOCKDIVIDER::DIV32K);

    GPIO::Port1 p1{};
    p1.setOutputLowOnPin(GPIO::PIN::P0);
    p1.setAsOutputPin(GPIO::PIN::P0);

    Pmm().unlockLPM5();

#ifdef MT_MSP430_USE_WDT_COMPILE_TIME_CALLBACKS

    constexpr static WDTA::Interrupt::WDT inter{
        []() {
            GPIO::Port1().toggleOutputOnPin(GPIO::PIN::P0);
        }
    };

#else

    WDTA::Interrupt::WDT inter;
    inter.registerCallback([]() {
        PIO::Port1().toggleOutputOnPin(GPIO::PIN::P0);
    });

#endif

    Sfr().enableInterrupt(SFR::INT::WATCHDOG_INTERVAL_TIMER);

    __bis_SR_register(LPM0_bits | GIE);// Enter LPM0, enable interrupts
    __no_operation();                  // For debug

#endif
}

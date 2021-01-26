#include "Examples/WDTA.hpp"
#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

void runWdtExample() {

#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
    WdtA wdt{};
    wdt.initIntervalTimer(WDTA::CLOCKSOURCE::SMCLK, WDTA::CLOCKDIVIDER::DIV32K);
    wdt.start();
#else
    WdtA wdt{};
    wdt.startIntervalTimer(WDTA::CLOCKSOURCE::SMCLK, WDTA::CLOCKDIVIDER::DIV32K);
#endif

    GPIO::Port1 p1{};
    p1.setOutputLowOnPin(GPIO::PIN::P0);
    p1.setAsOutputPin(GPIO::PIN::P0);

    Pmm pmm{};
    pmm.unlockLPM5();

#ifndef MT_MSP430_USE_WDT_COMPILE_TIME_CALLBACKS
    WDTA::Interrupt::WDT inter;
    inter.registerCallback([]() {
        GPIO::Port1 p1{};
        p1.toggleOutputOnPin(GPIO::PIN::P0);
    });
#endif

#ifdef MT_MSP430_USE_WDT_COMPILE_TIME_CALLBACKS
    WDTA::Interrupt::WDT inter{
        []() {
            GPIO::Port1 p1{};
            p1.toggleOutputOnPin(GPIO::PIN::P0);
        }
    };
#endif

    Sfr sfr{};
    sfr.enableInterrupt(SFR::INT::WATCHDOG_INTERVAL_TIMER);

    __bis_SR_register(LPM0_bits | GIE);// Enter LPM0, enable interrupts
    __no_operation();                  // For debug
};

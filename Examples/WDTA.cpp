#include "Examples/WDTA.hpp"
#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

#ifdef MT_MSP430_USE_WDT_COMPILE_TIME_CALLBACKS
constexpr auto isr = WDTA::Interrupt::makeInterrupt(
    WDTA::Interrupt::makeHandler(
        WDTA::Interrupt::WDTA::VEC1,
        []() {
            GPIO::Port1 p1{};
            p1.toggleOutputOnPin(GPIO::PIN::P0);
        }));
#endif

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
    WDTA::Interrupt::registerCallback([]() {
        GPIO::Port1 p1{};
        p1.toggleOutputOnPin(GPIO::PIN::P0);
    });
#endif

    Sfr sfr{};
    sfr.enableInterrupt(SFR::INT::WATCHDOG_INTERVAL_TIMER);

    __bis_SR_register(LPM0_bits | GIE);// Enter LPM0, enable interrupts
    __no_operation();                  // For debug
}


#ifdef MT_MSP430_USE_WDT_COMPILE_TIME_CALLBACKS
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = WDT_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(WDT_VECTOR)))
#endif
    void
    WDT_A_ISR(void) {
    std::get<isr.get_index(WDTA::Interrupt::VEC1)>(isr.m_vectors)();
}
#endif

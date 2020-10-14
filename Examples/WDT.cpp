#include "Examples/WDT.hpp"
#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;


#ifdef MT_MSP430_USE_WDT_COMPILE_TIME_CALLBACKS
constexpr auto isr = WDT::Interrupt::makeInterrupt(
    WDT::Interrupt::makeHandler(
        WDT::Interrupt::WDT::WDTA,
        []() {
            GPIO::Port1 p1{};
            p1.toggleOutputOnPin(PIN::P0);
        }));
#endif


void runWdtExample() {

    WDT::WdtA wdt{};
    wdt.initIntervalTimer(WDT::CLOCKSOURCE::SMCLK, WDT::CLOCKDIVIDER::DIV32K);
    wdt.start();

    GPIO::Port1 p1{};
    p1.setOutputLowOnPin(PIN::P0);
    p1.setAsOutputPin(PIN::P0);

    MT::Universal::Register<&PM5CTL0> pm5ctl{};
    pm5ctl.clear(LOCKLPM5);

#ifndef MT_MSP430_USE_WDT_COMPILE_TIME_CALLBACKS
    WDT::Interrupt::registerCallback([]() {
        GPIO::Port1 p1{};
        p1.toggleOutputOnPin(PIN::P0);
    });
#endif

    SFRIE1 |= WDTIE;// Enable WDT interrupt

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
    std::get<isr.get_index(WDT::Interrupt::WDTA)>(isr.m_vectors)();
}
#endif

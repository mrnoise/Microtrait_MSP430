#include "GPIO.hpp"
#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

#ifdef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS
constexpr auto isr = GPIO::Interrupt::makeInterrupt(
    GPIO::Interrupt::makeHandler(
        GPIO::Interrupt::PORTS::PORT2,
        []() {
            GPIO::Port1 p1{};
            GPIO::Port2 p2{};
            p2.clearInterrupt(PIN::P3);
            p1.toggleOutputOnPin(PIN::P0);
        }));
#endif

void runGpioExample() {

    WDT::WdtA wdt{};
    wdt.hold();

    MT::Universal::Register<&PM5CTL0> pm5ctl{};
    pm5ctl.clear(LOCKLPM5);


#ifndef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS
    GPIO::Interrupt::registerCallback(GPIO::Interrupt::PORTS::PORT2, []() {
        GPIO::Port1 p1{};
        GPIO::Port2 p2{};
        p2.clearInterrupt(PIN::P3);
        p1.toggleOutputOnPin(PIN::P0);
    });
#endif

    GPIO::Port1 p1{};
    GPIO::Port2 p2{};
    p1.setOutputLowOnPin(PIN::P0);
    p1.setAsOutputPin(PIN::P0);

    p2.setAsInputPinWithPullUp(PIN::P3);
    p2.selectInterruptEdge(INT_EDGE::HIGH_TO_LOW, PIN::P3);
    p2.enableInterrupt(PIN::P3);
    p2.clearInterrupt(PIN::P3);

    __bis_SR_register(GIE);
}


#ifdef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT2_VECTOR))) Port_2(void)
#else
#error Compiler not supported!
#endif
{
    std::get<isr.get_index(GPIO::Interrupt::PORTS::PORT2)>(isr.m_vectors)();
}
#endif

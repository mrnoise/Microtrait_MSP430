#include "GPIO.hpp"
#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

#ifdef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

constexpr auto isr = GPIO::Interrupt::makeInterrupt(

    GPIO::Interrupt::makeHandler(
        GPIO::Interrupt::PORTS::PORT1,
        []() {
            GPIO::Port1 p1{};
            p1.clearInterrupt(GPIO::PIN::P4);
            p1.toggleOutputOnPin(GPIO::PIN::P0);
        }),

    GPIO::Interrupt::makeHandler(
        GPIO::Interrupt::PORTS::PORT2,
        []() {
            GPIO::Port1 p1{};
            GPIO::Port2 p2{};
            p2.clearInterrupt(GPIO::PIN::P3);
            p1.toggleOutputOnPin(GPIO::PIN::P0);
        }));

#endif

void runGpioExample() {

    WdtA wdt{};
    wdt.hold();

    Pmm pmm{};
    pmm.unlockLPM5();

#ifndef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

    GPIO::Interrupt::registerCallback(GPIO::Interrupt::PORTS::PORT1, []() {
        GPIO::Port1 p1{};
        p1.clearInterrupt(GPIO::PIN::P4);
        p1.toggleOutputOnPin(GPIO::PIN::P0);
    });

    GPIO::Interrupt::registerCallback(GPIO::Interrupt::PORTS::PORT2, []() {
        GPIO::Port1 p1{};
        GPIO::Port2 p2{};
        p2.clearInterrupt(GPIO::PIN::P3);
        p1.toggleOutputOnPin(GPIO::PIN::P0);
    });

#endif

    GPIO::Port1 p1{};
    GPIO::Port2 p2{};
    p1.setOutputLowOnPin(GPIO::PIN::P0);
    p1.setAsOutputPin(GPIO::PIN::P0);

    p2.setAsInputPinWithPullUp(GPIO::PIN::P3);
    p2.selectInterruptEdge(GPIO::INT_EDGE::HIGH_TO_LOW, GPIO::PIN::P3);
    p2.enableInterrupt(GPIO::PIN::P3);
    p2.clearInterrupt(GPIO::PIN::P3);

    p1.setAsInputPinWithPullUp(GPIO::PIN::P4);
    p1.selectInterruptEdge(GPIO::INT_EDGE::HIGH_TO_LOW, GPIO::PIN::P4);
    p1.enableInterrupt(GPIO::PIN::P4);
    p1.clearInterrupt(GPIO::PIN::P4);

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

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT1_VECTOR))) Port_1(void)
#else
#error Compiler not supported!
#endif
{
    std::get<isr.get_index(GPIO::Interrupt::PORTS::PORT1)>(isr.m_vectors)();
}
#endif

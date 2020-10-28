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

    TIMERA::TA0 ta0;

    constexpr TIMERA::initContinuous param{
        TIMERA::CLOCKSOURCE::SMCLK,
        TIMERA::CLOCK_DIV::DIV1,
        TIMERA::GLOBAL_INT::DISABLE,
        TIMERA::CLEAR_COUNT_DIR::ENABLE,
        false
    };

    constexpr TIMERA::initCompare paramCom{
        TIMERA::CAPTURE_COMPARE::REGISTER0,
        TIMERA::CAPTURE_COMPARE_INT::ENABLE,
        TIMERA::COMPARE_OUTPUT::BITVALUE,
        COMPARE_VALUE
    };

    ta0.initContinuousMode(param);
    ta0.clearCaptureCompareInterrupt(TIMERA::CAPTURE_COMPARE::REGISTER0);
    ta0.initCompareMode(paramCom);
    ta0.startCounter(TIMERA::MODE::CONTINUOUS);

    //Enter LPM0, enable interrupts
    __bis_SR_register(LPM0_bits + GIE);

    //For debugger
    __no_operation();
}


// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(TIMER0_A0_VECTOR))) Timer_A(void)
#else
#error Compiler not supported!
#endif
{
    GPIO::Port1 p1{};
    p1.toggleOutputOnPin(GPIO::PIN::P0);

    TIMERA::TA0 ta0;
    ta0.setCompareValue(TIMERA::CAPTURE_COMPARE::REGISTER0, COMPARE_VALUE);
}

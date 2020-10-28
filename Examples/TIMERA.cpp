#include "TimerA.hpp"
#include "driverlib/MSP430FR5xx_6xx/driverlib.h"

#define GPIO_PORT_LED1 GPIO_PORT_P1
#define GPIO_PIN_LED1  GPIO_PIN0

#define COMPARE_VALUE 50000

void runTimerAExample() {

    //Stop Watchdog Timer
    WDT_A_hold(WDT_A_BASE);

    //Set LED1 as an output pin.
    GPIO_setAsOutputPin(
        GPIO_PORT_LED1,
        GPIO_PIN_LED1);

    PMM_unlockLPM5();


    //Initiaze compare mode
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);

    Timer_A_initCompareModeParam initCompParam = {};
    initCompParam.compareRegister              = TIMER_A_CAPTURECOMPARE_REGISTER_0;
    initCompParam.compareInterruptEnable       = TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;
    initCompParam.compareOutputMode            = TIMER_A_OUTPUTMODE_OUTBITVALUE;
    initCompParam.compareValue                 = COMPARE_VALUE;
    Timer_A_initCompareMode(TIMER_A0_BASE, &initCompParam);

    //Start timer in continuous mode sourced by SMCLK
    Timer_A_initContinuousModeParam initContParam = {};
    initContParam.clockSource                     = TIMER_A_CLOCKSOURCE_SMCLK;
    initContParam.clockSourceDivider              = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    initContParam.timerInterruptEnable_TAIE       = TIMER_A_TAIE_INTERRUPT_DISABLE;
    initContParam.timerClear                      = TIMER_A_DO_CLEAR;
    initContParam.startTimer                      = true;
    Timer_A_initContinuousMode(TIMER_A0_BASE, &initContParam);

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

    //Toggle LED1
    GPIO_toggleOutputOnPin(
        GPIO_PORT_LED1,
        GPIO_PIN_LED1);

    //Add Offset to CCR0
    Timer_A_setCompareValue(TIMER_A0_BASE,
        TIMER_A_CAPTURECOMPARE_REGISTER_0,
        COMPARE_VALUE);
}

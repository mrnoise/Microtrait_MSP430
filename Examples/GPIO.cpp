#include "Examples/GPIO.hpp"
#include "driverlib/MSP430FR5xx_6xx/driverlib.h"

#define GPIO_PORT_LED1 GPIO_PORT_P1
#define GPIO_PIN_LED1  GPIO_PIN0
#define GPIO_PORT_S1   GPIO_PORT_P1
#define GPIO_PIN_S1    GPIO_PIN1


void runGpioExample() {

    //Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);


    GPIO_setAsOutputPin(GPIO_PORT_LED1, GPIO_PIN_LED1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_S1, GPIO_PIN_S1);
    GPIO_enableInterrupt(GPIO_PORT_S1, GPIO_PIN_S1);
    GPIO_selectInterruptEdge(GPIO_PORT_S1, GPIO_PIN_S1, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_clearInterrupt(GPIO_PORT_S1, GPIO_PIN_S1);

    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN4);
    GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN4);
    GPIO_selectInterruptEdge(GPIO_PORT_P2, GPIO_PIN4, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN4);

    PMM_unlockLPM5();

    //Enter LPM3 w/interrupt
    __bis_SR_register(LPM3_bits + GIE);
}


// Port 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT1_VECTOR))) Port_1(void)
#else
#error Compiler not supported!
#endif
{
    switch (__even_in_range(P1IV, P1IV_P1IFG7)) {
        case P1IV_NONE: break;
        case P1IV_P1IFG0: break;
        case P1IV_P1IFG1:
            GPIO_toggleOutputOnPin(GPIO_PORT_LED1, GPIO_PIN_LED1);
            break;
        case P1IV_P1IFG2: break;
        case P1IV_P1IFG3: break;
        case P1IV_P1IFG4: break;
        case P1IV_P1IFG5: break;
        case P1IV_P1IFG6: break;
        case P1IV_P1IFG7: break;
    }
}


// Port 2 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT2_VECTOR))) Port_2(void)
#else
#error Compiler not supported!
#endif
{
    switch (__even_in_range(P2IV, P2IV_P2IFG7)) {
        case P2IV_NONE: break;
        case P2IV_P2IFG0: break;
        case P2IV_P2IFG1: break;
        case P2IV_P2IFG2: break;
        case P2IV_P2IFG3: break;
        case P2IV_P2IFG4:
            GPIO_toggleOutputOnPin(GPIO_PORT_LED1, GPIO_PIN_LED1);
            break;
        case P2IV_P2IFG5: break;
        case P2IV_P2IFG6: break;
        case P2IV_P2IFG7: break;
    }
}

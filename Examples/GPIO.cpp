#include "Examples/GPIO.hpp"
#include "driverlib/MSP430FR2xx_4xx/driverlib.h"

#define GPIO_PORT_LED1 GPIO_PORT_P1
#define GPIO_PIN_LED1  GPIO_PIN0
#define GPIO_PORT_LED2 GPIO_PORT_P1
#define GPIO_PIN_LED2  GPIO_PIN1
#define GPIO_PORT_S1   GPIO_PORT_P2
#define GPIO_PIN_S1    GPIO_PIN3
#define GPIO_PORT_S2   GPIO_PORT_P2
#define GPIO_PIN_S2    GPIO_PIN7

void runGpioExample() {

    //Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

    //Set LED1 to output direction
    GPIO_setAsOutputPin(GPIO_PORT_LED1, GPIO_PIN_LED1);

    //Enable S1 internal resistance as pull-Up resistance
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_S1, GPIO_PIN_S1);

    //S1 interrupt enabled
    GPIO_enableInterrupt(GPIO_PORT_S1, GPIO_PIN_S1);

    //S1 Hi/Lo edge
    GPIO_selectInterruptEdge(GPIO_PORT_S1, GPIO_PIN_S1, GPIO_HIGH_TO_LOW_TRANSITION);

    //S1 IFG cleared
    GPIO_clearInterrupt(GPIO_PORT_S1, GPIO_PIN_S1);

    PMM_unlockLPM5();

    //Enter LPM3 w/interrupt
    __bis_SR_register(LPM3_bits + GIE);
}


// Port 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT2_VECTOR))) Port_2(void)
#else
#error Compiler not supported!
#endif
{
    GPIO_clearInterrupt(GPIO_PORT_S1, GPIO_PIN_S1);
    GPIO_toggleOutputOnPin(GPIO_PORT_LED1, GPIO_PIN_LED1);
}

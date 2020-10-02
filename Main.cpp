
//#define USE_C_VARIANT

#include <msp430.h>

#ifndef USE_C_VARIANT

//#define RUN_TESTS

#include <stdint.h>
#include "MicroTrait/Misc/EnumBits.hpp"
#include "MicroTrait/MSP430/GPIO/PortRegister.hpp"
#include "MicroTrait/Universal/Register.hpp"
#ifdef RUN_TESTS
#include "MicroTrait/Tests/TestRunner.hpp"
#endif

using namespace MT::MSP430;

#else

//#define USE_DRIVERLIB

#ifdef USE_DRIVERLIB
#include "driverlib/MSP430FR2xx_4xx/driverlib.h"

#define GPIO_PORT_LED1          GPIO_PORT_P1
#define GPIO_PIN_LED1           GPIO_PIN0
#define GPIO_PORT_LED2          GPIO_PORT_P1
#define GPIO_PIN_LED2           GPIO_PIN1
#define GPIO_PORT_S1            GPIO_PORT_P2
#define GPIO_PIN_S1             GPIO_PIN3
#define GPIO_PORT_S2            GPIO_PORT_P2
#define GPIO_PIN_S2             GPIO_PIN7
#endif

#endif


int main(void)
{

#ifdef USE_C_VARIANT

#ifdef USE_DRIVERLIB

  //Stop watchdog timer
	WDT_A_hold(WDT_A_BASE);

	//Set LED1 to output direction
	GPIO_setAsOutputPin( GPIO_PORT_LED1, GPIO_PIN_LED1  );

	//Enable S1 internal resistance as pull-Up resistance
	GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_S1,GPIO_PIN_S1);

	//S1 interrupt enabled
	GPIO_enableInterrupt(GPIO_PORT_S1,GPIO_PIN_S1);

	//S1 Hi/Lo edge
	GPIO_selectInterruptEdge(GPIO_PORT_S1,GPIO_PIN_S1,GPIO_HIGH_TO_LOW_TRANSITION);

	//S1 IFG cleared
	GPIO_clearInterrupt(GPIO_PORT_S1,GPIO_PIN_S1);

	PMM_unlockLPM5();

	//Enter LPM3 w/interrupt
	__bis_SR_register(LPM3_bits + GIE);


#else

	WDTCTL = WDTPW | WDTHOLD;
    // Disable the GPIO power-on default high-impedance mode
	// to activate previously configured port settings
	PM5CTL0 &= ~LOCKLPM5;

	    // Configure GPIO
    P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT0;                          // Set P1.0 to output direction

    P2OUT |= BIT3;                          // Configure P1.3 as pulled-up
    P2REN |= BIT3;                          // P1.3 pull-up register enable
    P2IES |= BIT3;                          // P1.3 Hi/Low edge
    P2IE |= BIT3;                           // P1.3 interrupt enabled
    P2IFG &= ~BIT3;                         // P1.3 IFG cleared

    __bis_SR_register(GIE);
#endif

    while(1)
    {

    }

#else

    MT::Universal::Register <&WDTCTL> wdt {};
	MT::Universal::Register <&PM5CTL0> pm5ctl {};
	wdt.override(WDTPW | WDTHOLD);
	pm5ctl.clear(LOCKLPM5);

#ifdef RUN_TESTS
	 MT::Tests::run();
#endif

	 GPIO::Port1 p1{};
	 GPIO::Port2 p2{};
	 GPIO::Port1 p3{};
	 p1.setOutputLowOnPin(PIN::P0);
	 p1.setAsOutputPin(PIN::P0);

	 p2.setAsInputPinWithPullUp(PIN::P3);
	 p2.selectInterruptEdge(INT_EDGE::HIGH_TO_LOW,PIN::P3);
	 p2.enableInterrupt(PIN::P3);
	 p2.clearInterrupt(PIN::P3);

    __bis_SR_register(GIE);

    while(1)
	{

	}
#endif


}

// Port 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT2_VECTOR))) Port_2 (void)
#else
#error Compiler not supported!
#endif
{

#ifdef USE_C_VARIANT

#ifdef USE_DRIVERLIB
	GPIO_clearInterrupt(GPIO_PORT_S1,GPIO_PIN_S1);
	GPIO_toggleOutputOnPin(GPIO_PORT_LED1,GPIO_PIN_LED1);
#else
	P2IFG &= ~BIT3; // Clear P1.3 IFG
	P1OUT ^= BIT0;
#endif

#else

	GPIO::Port1 p1{};
	GPIO::Port2 p2{};
	p2.clearInterrupt(PIN::P3);
	p1.toggleOutputOnPin(PIN::P0);

#endif

}


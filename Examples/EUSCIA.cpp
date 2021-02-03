#include "Examples/Settings.hpp"
#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

#ifdef EXAMPLE_RUN_EUSCIA
static constexpr uint8_t c_checkByte = 123;
#endif

void runEusciAExample() {

#ifdef EXAMPLE_RUN_EUSCIA

    WdtA wdt{};
    wdt.hold();

    GPIO::Port3 p3;
    p3.setAsPeripheralModuleFunctionInputPin(GPIO::MODULE_FUNC::PRIMARY, GPIO::PIN::P4 | GPIO::PIN::P5);

    GPIO::Port1 p1;
    p1.setAsOutputPin(GPIO::PIN::P0);
    p1.setOutputLowOnPin(GPIO::PIN::P0);

    Pmm pmm{};
    pmm.unlockLPM5();

#ifdef MT_MSP430_USE_EUSCIA_UART_COMPILE_TIME_CALLBACKS
    constexpr static EUSCIA::UART::Interrupt::A1 int1{
        []([[maybe_unused]] const EUSCIA::UART::INT src) {
            EUSCIA::UART::A1 a1;
            const uint8_t    rx = a1.receiveData();
            if (rx != c_checkByte)// Check value
            {
                GPIO::Port1 p;
                p.setOutputHighOnPin(GPIO::PIN::P0);

                while (1)
                    ;
            }
            __bic_SR_register_on_exit(CPUOFF);// Exit LPM0 on reti
        }
    };
#else
    EUSCIA::UART::Interrupt::A1 int1;
    int1.setIntrinsic(ISR_INTRINSICS::LEAVE_LOW_POWER);
    int1.registerCallback(
        []([[maybe_unused]] const EUSCIA::UART::INT src) {
            EUSCIA::UART::A1 a1;
            const uint8_t    rx = a1.receiveData();
            if (rx != c_checkByte)// Check value
            {
                GPIO::Port1 p;
                p.setOutputHighOnPin(GPIO::PIN::P0);
                while (1)
                    ;
            }
        });
#endif

    constexpr EUSCIA::UART::initParam param{
        // Baudrate 9600 at 1MHz SMCLCK
        EUSCIA::UART::CLOCKSOURCE::SMCLK,
        6,
        8,
        17,
        EUSCIA::UART::PARITY::NO,
        EUSCIA::UART::ENDIAN::LSB_FIRST,
        EUSCIA::UART::STOPBIT::ONE,
        EUSCIA::UART::MODE::UART,
        EUSCIA::UART::BAUD_GENERATION::OVERSAMPLING
    };

    EUSCIA::UART::A1 a1;
    a1.init(param);
    a1.enable();
    a1.clearInterrupt(EUSCIA::UART::INT::RECEIVE);
    a1.enableInterrupt(EUSCIA::UART::INT::RECEIVE, EUSCIA::UART::INT_EXT::NONE);

    while (1) {
        // Load data onto buffer
        a1.transmitData(c_checkByte);
        __bis_SR_register(LPM0_bits | GIE);// Enter LPM0, interrupts enabled
    }
#endif
}

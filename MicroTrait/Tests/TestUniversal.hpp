
#ifndef MICROTRAIT_TESTS_TESTUNIVERSAL_HPP_
#define MICROTRAIT_TESTS_TESTUNIVERSAL_HPP_

#include "MicroTrait/Universal/Register.hpp"
#include "MicroTrait/Universal/Interrupt.hpp"
#include <assert.h>


namespace MT::Tests::Universal::Internal {

using namespace MT::Misc;


void runRegisterU8() noexcept {

    static volatile uint8_t       val = 0;
    MT::Universal::Register<&val> reg{};
    reg.set(0xFF);
    assert(val == 0xFF);

    reg.clear(0xFF);
    reg.set(0x00);
    assert(val == 0);

    reg.override(0b0001);
    assert(val == 0b0001);

    reg.override(0b00010001);
    assert(val == 0b00010001);

    uint8_t test = 0;
    for (uint8_t i = 0; i < 8; ++i) {
        reg.override(1U << i);
        test = (1U << i);
        assert(val == test);
        assert(val == reg.get());
    }

    reg.clear(0xFF);
    test = 0;
    for (uint8_t i = 0; i < 8; ++i) {
        reg.set(1U << i);
        test |= (1U << i);
        assert(val == test);
        assert(val == reg.get());
    }

    reg.set(0xFF);
    test = 0xFF;
    for (uint8_t i = 0; i < 8; ++i) {
        reg.clear(1U << i);
        test &= ~(1U << i);
        assert(val == test);
        assert(val == reg.get());
    }


    BITS8 testB = BITS8::B0;
    for (uint8_t i = 0; i < 8; ++i) {
        reg.override(static_cast<BITS8>(i));
        testB = (static_cast<BITS8>(i));
        assert(val == static_cast<uint8_t>(testB));
        assert(val == reg.get());
    }

    reg.clear(0xFF);
    testB = static_cast<BITS8>(0);
    for (uint8_t i = 0; i < 8; ++i) {
        reg.set(static_cast<BITS8>(i));
        testB |= (static_cast<BITS8>(i));
        assert(val == static_cast<uint8_t>(testB));
        assert(val == reg.get());
    }

    reg.set(0xFF);
    testB = static_cast<BITS8>(0xFF);
    for (uint8_t i = 0; i < 8; ++i) {
        reg.clear(static_cast<BITS8>(i));
        testB &= ~(static_cast<BITS8>(i));
        assert(val == static_cast<uint8_t>(testB));
        assert(val == reg.get());
    }

    reg.clear(0xFF);
    reg.set(1 << 5);
    bool comp = reg.compare(1 << 5);
    assert(comp == true);

    reg.set(0xFF);
    reg.clear(1 << 5);
    comp = reg.compare(1 << 5);
    assert(comp == false);

    reg.clear(0xFF);
    reg.set(BITS8::B5);
    comp = reg.compare(BITS8::B5);
    assert(comp == true);

    reg.set(0xFF);
    reg.clear(BITS8::B5);
    comp = reg.compare(BITS8::B5);
    assert(comp == false);
}

void runRegisterU16() noexcept {

    static volatile uint16_t      val = 0;
    MT::Universal::Register<&val> reg{};
    reg.set(0xFFFF);
    assert(val == 0xFFFF);

    reg.clear(0xFFFF);
    reg.set(0x0000);
    assert(val == 0);

    reg.override(0b0001);
    assert(val == 0b0001);

    reg.override(0b00010001);
    assert(val == 0b00010001);

    uint16_t test = 0;
    for (uint16_t i = 0; i < 16; ++i) {
        reg.override(1U << i);
        test = (1U << i);
        assert(val == test);
        assert(val == reg.get());
    }

    reg.clear(0xFFFF);
    test = 0;
    for (uint16_t i = 0; i < 16; ++i) {
        reg.set(1U << i);
        test |= (1U << i);
        assert(val == test);
        assert(val == reg.get());
    }

    reg.set(0xFFFF);
    test = 0xFFFF;
    for (uint16_t i = 0; i < 16; ++i) {
        reg.clear(1U << i);
        test &= ~(1U << i);
        assert(val == test);
        assert(val == reg.get());
    }


    BITS16 testB = BITS16::B0;
    for (uint16_t i = 0; i < 16; ++i) {
        reg.override(static_cast<BITS16>(i));
        testB = (static_cast<BITS16>(i));
        assert(val == static_cast<uint16_t>(testB));
        assert(val == reg.get());
    }

    reg.clear(0xFFFF);
    testB = static_cast<BITS16>(0);
    for (uint16_t i = 0; i < 16; ++i) {
        reg.set(static_cast<BITS16>(i));
        testB |= (static_cast<BITS16>(i));
        assert(val == static_cast<uint16_t>(testB));
        assert(val == reg.get());
    }

    reg.set(0xFFFF);
    testB = static_cast<BITS16>(0xFFFF);
    for (uint16_t i = 0; i < 16; ++i) {
        reg.clear(static_cast<BITS16>(i));
        testB &= ~(static_cast<BITS16>(i));
        assert(val == static_cast<uint16_t>(testB));
        assert(val == reg.get());
    }

    reg.clear(0xFFFF);
    reg.set(1U << 10U);
    bool comp = reg.compare(1U << 10U);
    assert(comp == true);

    reg.set(0xFFFF);
    reg.clear(1U << 10U);
    comp = reg.compare(1U << 10U);
    assert(comp == false);

    reg.clear(0xFFFF);
    reg.set(BITS16::B10);
    comp = reg.compare(BITS16::B10);
    assert(comp == true);

    reg.set(0xFFFF);
    reg.clear(BITS16::B10);
    comp = reg.compare(BITS16::B10);
    assert(comp == false);
}

void runRegisterU32() noexcept {

    static volatile uint32_t      val = 0;
    MT::Universal::Register<&val> reg{};
    reg.set(0xFFFFFFFF);
    assert(val == 0xFFFFFFFF);

    reg.clear(0xFFFFFFFF);
    reg.set(0x0000);
    assert(val == 0);

    reg.override(0b0001);
    assert(val == 0b0001);

    reg.override(0b00010001);
    assert(val == 0b00010001);

    uint32_t test = 0;
    for (uint32_t i = 0; i < 32; ++i) {
        reg.override(1U << i);
        test = (1U << i);
        assert(val == test);
        assert(val == reg.get());
    }

    reg.clear(0xFFFFFFFF);
    test = 0;
    for (uint32_t i = 0; i < 32; ++i) {
        reg.set(1U << i);
        test |= (1U << i);
        assert(val == test);
        assert(val == reg.get());
    }

    reg.set(0xFFFFFFFF);
    test = 0xFFFFFFFF;
    for (uint32_t i = 0; i < 32; ++i) {
        reg.clear(1U << i);
        test &= ~(1U << i);
        assert(val == test);
        assert(val == reg.get());
    }


    BITS32 testB = BITS32::B0;
    for (uint32_t i = 0; i < 32; ++i) {
        reg.override(static_cast<BITS32>(i));
        testB = (static_cast<BITS32>(i));
        assert(val == static_cast<uint32_t>(testB));
        assert(val == reg.get());
    }

    reg.clear(0xFFFFFFFF);
    testB = static_cast<BITS32>(0);
    for (uint32_t i = 0; i < 32; ++i) {
        reg.set(static_cast<BITS32>(i));
        testB |= (static_cast<BITS32>(i));
        assert(val == static_cast<uint32_t>(testB));
        assert(val == reg.get());
    }

    reg.set(0xFFFFFFFF);
    testB = static_cast<BITS32>(0xFFFFFFFF);
    for (uint32_t i = 0; i < 32; ++i) {
        reg.clear(static_cast<BITS32>(i));
        testB &= ~(static_cast<BITS32>(i));
        assert(val == static_cast<uint32_t>(testB));
        assert(val == reg.get());
    }

    reg.clear(0xFFFFFFFF);
    reg.set(1UL << 18UL);
    bool comp = reg.compare(1UL << 18UL);
    assert(comp == true);

    reg.set(0xFFFFFFFF);
    reg.clear(1UL << 18UL);
    comp = reg.compare(1UL << 18UL);
    assert(comp == false);

    reg.clear(0xFFFFFFFF);
    reg.set(BITS32::B18);
    comp = reg.compare(BITS32::B18);
    assert(comp == true);

    reg.set(0xFFFFFFFF);
    reg.clear(BITS32::B18);
    comp = reg.compare(BITS32::B18);
    assert(comp == false);
}

bool toggle = true;
void runInterrupt() noexcept {

    enum class VECTORS {
        VECTOR1 = 0,
        VECTOR2,
        VECTOR3,
        VECTOR4,
        VECTOR5,
        VECTOR6,
        VECTOR7,
        VECTOR8
    };

    using namespace MT::Universal::Interrupt;

    constexpr auto isr = makeInterrupt(
        makeHandler(
            VECTORS::VECTOR1,
            []() {
                toggle = false;
            }));

    assert(toggle == true);

    //fake call -> normally in interrupt vector
    std::get<isr.get_index(VECTORS::VECTOR1)>(isr.m_vectors)();

    assert(toggle == false);
}


void runMetaU8() noexcept {
    static volatile uint8_t       val = 0;
    MT::Universal::Register<&val> reg{};

    volatile BITS8 v = BITS8::B0;
    reg.set(v);

    const BITS8 c = BITS8::B0;
    reg.set(c);

    const volatile BITS8 cv = BITS8::B0;
    reg.set(cv);
}

void runMetaU16() noexcept {
    static volatile uint16_t      val = 0;
    MT::Universal::Register<&val> reg{};

    volatile BITS16 v = BITS16::B0;
    reg.set(v);

    const BITS16 c = BITS16::B0;
    reg.set(c);

    const volatile BITS16 cv = BITS16::B0;
    reg.set(cv);
}

void runMetaU32() noexcept {
    static volatile uint32_t      val = 0;
    MT::Universal::Register<&val> reg{};

    volatile BITS32 v = BITS32::B0;
    reg.set(v);

    const BITS32 c = BITS32::B0;
    reg.set(c);

    const volatile BITS32 cv = BITS32::B0;
    reg.set(cv);
}

}// namespace MT::Tests::Universal::Internal

namespace MT::Tests::Universal {
void run() noexcept {
    Internal::runRegisterU8();
    Internal::runRegisterU16();
    Internal::runRegisterU32();
    Internal::runInterrupt();
    Internal::runMetaU8();
    Internal::runMetaU16();
    Internal::runMetaU32();
}
}// namespace MT::Tests::Universal


#endif /* MICROTRAIT_TESTS_TESTUNIVERSAL_HPP_ */

/*
 * Test_Enumerator.h
 *
 *  Created on: Jun 21, 2017
 *      Author: jyates
 */

#ifndef TESTING_TYPES_TEST_ENUMERATOR_H_
#define TESTING_TYPES_TEST_ENUMERATOR_H_

#include <stdexcept>

#include <sstream>
#include <cxxtest/TestSuite.h>

#include "../Types/Enumerator.h"

class Test_Enumerator: public CxxTest::TestSuite {
public:
    void setUp   () { }
    void tearDown() { }

    void testAdvance() {
        TestEnum goodEnum = TestEnum::ONE;

        Enumeration::advance(goodEnum);
        TS_ASSERT_EQUALS(goodEnum, TestEnum::TWO);

        Enumeration::advance(goodEnum);
        TS_ASSERT_EQUALS(goodEnum, TestEnum::THR);

        Enumeration::advance(goodEnum);
        TS_ASSERT_EQUALS(goodEnum, TestEnum::FIV);

        Enumeration::advance(goodEnum);
        TS_ASSERT_EQUALS(goodEnum, TestEnum::SIX);

        Enumeration::advance(goodEnum);
        TS_ASSERT_EQUALS(goodEnum, TestEnum::ONE);

        TestEnum errorEnum = TestEnum::FOU;
        try {
            Enumeration::advance(errorEnum);
            TS_FAIL("Expected exception to occur for invalid ENUM");
        } catch (std::runtime_error& e) {
            TS_ASSERT_EQUALS(Enumeration::INVALID_ENUM_FOR_ADVANCE, e.what());
            TS_TRACE(std::string("Expectation found: ") + e.what());
        }
    }

    void testReverse() {
        TestEnum goodEnum = TestEnum::SIX;

        Enumeration::reverse(goodEnum);
        TS_ASSERT_EQUALS(goodEnum, TestEnum::FIV);

        Enumeration::reverse(goodEnum);
        TS_ASSERT_EQUALS(goodEnum, TestEnum::THR);

        Enumeration::reverse(goodEnum);
        TS_ASSERT_EQUALS(goodEnum, TestEnum::TWO);

        Enumeration::reverse(goodEnum);
        TS_ASSERT_EQUALS(goodEnum, TestEnum::ONE);

        Enumeration::reverse(goodEnum);
        TS_ASSERT_EQUALS(goodEnum, TestEnum::SIX);

        TestEnum errorEnum = TestEnum::FOU;
        try {
            Enumeration::reverse(errorEnum);
            TS_FAIL("Expected exception to occur for invalid ENUM");
        } catch (std::runtime_error& e) {
            TS_ASSERT_EQUALS(Enumeration::INVALID_ENUM_FOR_REVERSE, e.what());
            TS_TRACE(std::string("Expectation found: ") + e.what());
        }
    }

    void testConvert() {
        TestEnum enumOne = TestEnum::ONE;
        TS_ASSERT_EQUALS(Enumeration::convert(enumOne), static_cast<unsigned long long>(TestEnum::ONE));

        TestEnum enumTwo = TestEnum::TWO;
        TS_ASSERT_EQUALS(Enumeration::convert(enumTwo), static_cast<unsigned long long>(TestEnum::TWO));

        TestEnum enumThr = TestEnum::THR;
        TS_ASSERT_EQUALS(Enumeration::convert(enumThr), static_cast<unsigned long long>(TestEnum::THR));

        TestEnum enumFiv = TestEnum::FIV;
        // Special case: normally, if all enum values were included in the typedef for Enumeration (below),
        //  this value would be equal to 4, not 3. However, because we left out the FOU enumeration, FIV
        //  takes the value that would have belonged to FOU. This is intentional and expected. The enumerator
        //  cannot account for enumerations that are not included in the template. Do not compare the value
        //  return by convert with a static_cast.
        TS_ASSERT_EQUALS(Enumeration::convert(enumFiv), 3);

        TestEnum enumSix = TestEnum::SIX;
        // See above for explanation on why the expected result is 4, and not 5.
        TS_ASSERT_EQUALS(Enumeration::convert(enumSix), 4);

        TestEnum errorEnum = TestEnum::FOU;
        try {
            Enumeration::convert(errorEnum);
            TS_FAIL("Expected exception to occur for invalid ENUM");
        } catch (std::runtime_error& e) {
            TS_ASSERT_EQUALS(Enumeration::INVALID_ENUM_FOR_CONVERSION, e.what());
            TS_TRACE(std::string("Expectation found: ") + e.what());
        }
    }

private:
    enum class TestEnum {
        ONE,
        TWO,
        THR,
        FOU,
        FIV,
        SIX
    };

    typedef Enumerator<TestEnum,
            TestEnum::ONE,
            TestEnum::TWO,
            TestEnum::THR, // purposely leaving out FOU enumeration
            TestEnum::FIV,
            TestEnum::SIX> Enumeration;
};

#endif // TESTING_TYPES_TEST_ENUMERATOR_H_

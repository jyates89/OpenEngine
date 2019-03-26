/*
 * Test_Var.h
 *
 *  Created on: Jul 4, 2017
 *      Author: jyates
 */

#ifndef TESTING_TYPES_SQL_TEST_VAR_H_
#define TESTING_TYPES_SQL_TEST_VAR_H_

#include <string>
#include <sstream>
#include <cxxtest/TestSuite.h>

#include "Types/SQL/Var.h"

class Test_Var: public CxxTest::TestSuite {
public:
    void setUp   () { }
    void tearDown() { }

    void testInt() {
        int value = 5;
        Var intVal;
        intVal.set(value);
        TS_ASSERT_EQUALS(intVal.get<int>(), value);
    }

    void testIntasChar() {
        int value = 5;
        Var intVal;
        intVal.set(value);
        TS_ASSERT_EQUALS(intVal.get<char>(), value);
    }

    void testIntasDouble() {
        int value = 5;
        double dblVal = 5.0;
        Var intVal;
        intVal.set(value);
        TS_ASSERT_EQUALS(intVal.get<double>(), dblVal);
    }

    void testIntasString() {
        int value = 5;
        std::string strVal = "5";
        Var intVal;
        intVal.set(value);
        TS_ASSERT_EQUALS(intVal.get<std::string>(), strVal);
    }

    void testDbl() {
        double value = 3.14;
        Var dblVal;
        dblVal.set(value);
        TS_ASSERT_EQUALS(dblVal.get<double>(), value);
    }

    void testDblasInt() {
        double value = 3.14;
        int intVal = 3;
        Var dblVal;
        dblVal.set(value);
        TS_ASSERT_EQUALS(dblVal.get<int>(), intVal);
    }

    void testDblasChar() {
        double value = 3.14;
        char chrVal = 3;
        Var dblVal;
        dblVal.set(value);
        TS_ASSERT_EQUALS(dblVal.get<char>(), chrVal);
    }

    void testDblasString() {
        double value = 3.14;
        std::string strVal = "3.140000";
        Var dblVal;
        dblVal.set(value);
        TS_ASSERT_EQUALS(dblVal.get<std::string>(), strVal);
    }

    void testChr() {
        char value = 'x';
        Var chrVal;
        chrVal.set(value);
        TS_ASSERT_EQUALS(chrVal.get<char>(), value);
    }

    void testChrAsInt() {
        char value = 'x';
        int intVal = 0x78;
        Var chrVal;
        chrVal.set(value);
        TS_ASSERT_EQUALS(chrVal.get<int>(), intVal);
    }

    void testChrAsDouble() {
        char value = 'x';
        double dblVal = 120.0;
        Var chrVal;
        chrVal.set(value);
        TS_ASSERT_EQUALS(chrVal.get<double>(), dblVal);
    }

    void testChrAsString() {
        char value = 'x';
        std::string strVal = "x";
        Var chrVal;
        chrVal.set(value);
        TS_ASSERT_EQUALS(chrVal.get<std::string>(), strVal);
    }

    void testStr() {
        std::string value = "5";
        Var strVal;
        strVal.set(value);
        TS_ASSERT_EQUALS(strVal.get<std::string>(), value);
    }

    void testStrAsInt() {
        std::string value = "5";
        int intVal = 5;
        Var strVal;
        strVal.set(value);
        TS_ASSERT_EQUALS(strVal.get<int>(), intVal);
    }

    void testStrAsDouble() {
        std::string value = "5";
        double dblVal = 5.0;
        Var strVal;
        strVal.set(value);
        TS_ASSERT_EQUALS(strVal.get<double>(), dblVal);
    }

    void testStrAsChar() {
        std::string value = "5";
        char chrVal = '5';
        Var strVal;
        strVal.set(value);
        TS_ASSERT_EQUALS(strVal.get<char>(), chrVal);
    }

private:

};

#endif // TESTING_TYPES_SQL_TEST_VAR_H_

/*
 * Test_Flyweight.h
 *
 *  Created on: Jun 5, 2017
 *      Author: jyates
 */

#ifndef TESTING_PATTERNS_TEST_FLYWEIGHT_H_
#define TESTING_PATTERNS_TEST_FLYWEIGHT_H_

#include <sstream>
#include <cxxtest/TestSuite.h>

#include <climits>

#include "../../Types/StandardDefines.h"

#include "../../Patterns/Flyweight.h"
#include "../../Patterns/FlyweightFactory.h"

class Break {
public:
    Break() : m_breakID(0) {
    }

    Break(int id) : m_breakID(id) {

    }

    ~Break() {}

    int getID() const {
        return m_breakID;
    }
private:
    int m_breakID;
};

class STB {
public:
    int em_STBID;

    void setCurrentBreak(std::shared_ptr<Break> currentBreak) {
        m_currentBreak = currentBreak;
    }

    int currentBreakID() const {
        if (m_currentBreak == nullptr) {
            throw std::runtime_error("Current break is a nullptr.");
        }
        return m_currentBreak->getID();
    }

private:
    std::shared_ptr<Break> m_currentBreak;
};

class TestWeight : public Flyweight<STB, std::shared_ptr<Break>> {
public:
    TestWeight(int id = 0) {
        m_intrinsicState->em_STBID = id;
    }
    ~TestWeight() {}

    int getID() const {
        return m_intrinsicState->em_STBID;
    }

    int getBreakID() const {
        return m_intrinsicState->currentBreakID();
    }

    void calculateState(std::shared_ptr<Break> currentBreak) {
        m_intrinsicState->setCurrentBreak(currentBreak);
    }

};

class Test_Flyweight: public CxxTest::TestSuite {
public:
    void setUp   () { }
    void tearDown() { }

    void testFlyweight() {
        FlyweightFactory<TestWeight, STB, std::shared_ptr<Break>> factory;
        const std::uint8_t OBJECT_COUNT = CHAR_MAX;
        UniqueID uniqueIDs[OBJECT_COUNT];

        int breakID = 5;
        std::shared_ptr<Break> someBreak = std::make_shared<Break>(breakID);
        for (std::size_t index = 0; index < OBJECT_COUNT; index++) {
            std::shared_ptr<TestWeight> testWeight = std::make_shared<TestWeight>(index);
            factory.getInstance(uniqueIDs[index], testWeight)->calculateState(someBreak);
        }

        for (std::size_t index = 0; index < OBJECT_COUNT; index++) {
            std::stringstream flyweightResult("ID: ", std::ios::app|std::ios::out);
            flyweightResult << factory.getInstance(uniqueIDs[index])->getID();
            flyweightResult << " <-> Break: " << factory.getInstance(uniqueIDs[index])->getBreakID();
            TS_TRACE(flyweightResult.str().c_str());

            TS_ASSERT(static_cast<std::size_t>(factory.getInstance(uniqueIDs[index])->getID())
                    == index);
            TS_ASSERT(factory.getInstance(uniqueIDs[index])->getBreakID() == breakID);
        }
    }

private:

};

#endif // TESTING_PATTERNS_TEST_FLYWEIGHT_H_

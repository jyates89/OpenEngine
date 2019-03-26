/*
 * Test_State.h
 *
 *  Created on: Jun 5, 2017
 *      Author: jyates
 */

#ifndef TESTING_PATTERNS_TEST_STATE_H_
#define TESTING_PATTERNS_TEST_STATE_H_

#include <sstream>
#include <cxxtest/TestSuite.h>

#include <cstring>

#include "../Types/StandardDefines.h"

#include "../../Patterns/State.h"
#include "../../Patterns/StateContext.h"

class StateInfo {
public:
    int someData;

    StateInfo() : someData(0) {}
    ~StateInfo() {}

    void doStuff() {
        ++someData;
    }
};

class OnState : public State<StateInfo> {
public:
    std::string stateDescription() const {
        return "On state!";
    }

    void stateStarting() {
        TS_TRACE("preparing to enter ON state\n");
    }

    void handleStateAction() {
        TS_TRACE("handling ON state action\n");
        getStateData().doStuff();
    }

    void stateEnding() {
        TS_TRACE("preparing to leave ON state\n");
    }

private:

};

class OffState : public State<StateInfo> {
public:
    std::string stateDescription() const {
        return "Off state!";
    }

    void stateStarting() {
        TS_TRACE("preparing to enter OFF state\n");
    }

    void handleStateAction() {
        TS_TRACE("handling OFF state action\n");
        getStateData().doStuff();
    }

    void stateEnding() {
        TS_TRACE("preparing to leave OFF state\n");
    }
};

class Test_State: public CxxTest::TestSuite {
public:
    void setUp   () { }
    void tearDown() { }

    void testState() {
        StateContext<StateInfo> stateContext;

        std::unique_ptr<OnState> onState(new OnState);
        try {
            stateContext.stateChange(std::move(onState));
        } catch (const std::invalid_argument& e) {
            std::stringstream exceptionResult("Exception: ", std::ios::app|std::ios::out);
            exceptionResult << e.what();
            TS_TRACE(exceptionResult.str().c_str());
        }
        std::stringstream onDescription("Current state description: ", std::ios::app|std::ios::out);
        onDescription << stateContext.currentStateDescription().c_str();
        TS_ASSERT(std::strcmp("On state!", stateContext.currentStateDescription().c_str()) == 0);
        TS_TRACE(onDescription.str().c_str());

        stateContext.executeCurrentStateHandler();

        std::unique_ptr<OffState> offState(new OffState);
        try {
            stateContext.stateChange(std::move(offState));
        } catch (const std::invalid_argument& e) {
            std::stringstream exceptionResult("Exception: ", std::ios::app|std::ios::out);
            exceptionResult << e.what();
            TS_TRACE(exceptionResult.str().c_str());
        }
        std::stringstream offDescription("Current state description: ", std::ios::app|std::ios::out);
        offDescription << stateContext.currentStateDescription().c_str();
        TS_ASSERT(std::strcmp("Off state!", stateContext.currentStateDescription().c_str()) == 0);
        TS_TRACE(offDescription.str().c_str());

        stateContext.executeCurrentStateHandler();

        stateContext.undoStateChange();
        TS_ASSERT(std::strcmp("On state!", stateContext.currentStateDescription().c_str()) == 0);
        stateContext.executeCurrentStateHandler();

        stateContext.redoStateChange();
        TS_ASSERT(std::strcmp("Off state!", stateContext.currentStateDescription().c_str()) == 0);
        stateContext.executeCurrentStateHandler();
    }

private:

};

#endif // TESTING_PATTERNS_TEST_STATE_H_

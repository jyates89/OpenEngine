/*
 * Test_Command.h
 *
 *  Created on: Jun 5, 2017
 *      Author: jyates
 */

#ifndef TESTING_PATTERNS_TEST_COMMAND_H_
#define TESTING_PATTERNS_TEST_COMMAND_H_

#include <cxxtest/TestSuite.h>

#include <memory>
#include <vector>
#include <sstream>

#include "../../Types/StandardDefines.h"

#include "../../Patterns/Command.h"

class Metadata {
public:
    Metadata(int some = 0): m_data(some) {}
    virtual ~Metadata() {}

    virtual int getSomeData() = 0;

    void addData(int val) {
        m_data += val;
    }

protected:
    int m_data;
};

class SpecificData: public Metadata {
public:
    SpecificData() : Metadata(10) {}
    virtual ~SpecificData() {}

    int getSomeData() {
        return m_data;
    }
};

class SomeCommand: public Command<SpecificData> {
public:
    SomeCommand() : val(5) {}
    virtual ~SomeCommand() {}

    void execute() {
        em_commandData.addData(val);
    }

private:
    int val;
};

class AnotherCommand: public Command<SpecificData> {
public:
    AnotherCommand() : val(10) {}
    virtual ~AnotherCommand() {}

    void execute() {
        em_commandData.addData(val);
    }

private:
    int val;
};

class Test_Command: public CxxTest::TestSuite {
public:
    void setUp   () { }
    void tearDown() { }

    void testCommand() {
        std::vector<std::shared_ptr<Command<SpecificData>>> commandList;

        std::shared_ptr<SomeCommand> command(new SomeCommand);
        commandList.push_back(command);

        std::shared_ptr<AnotherCommand> anotherCommand(new AnotherCommand);
        commandList.push_back(anotherCommand);

        for (std::size_t index = 0; index < commandList.size(); index++) {
            commandList[index]->execute();
        }

        std::stringstream commandTestOne("Command(SomeCommand) details: ",
                std::ios::app|std::ios::out);
        commandTestOne << command->em_commandData.getSomeData();
        TS_TRACE(commandTestOne.str().c_str());

        std::stringstream commandTestTwo("Command(AnotherCommand) details: ",
                std::ios::app|std::ios::out);
        commandTestTwo << anotherCommand->em_commandData.getSomeData();
        TS_TRACE(commandTestTwo.str().c_str());

        TS_ASSERT(command->em_commandData.getSomeData() != anotherCommand->em_commandData.getSomeData());
    }

private:

};

#endif // TESTING_PATTERNS_TEST_COMMAND_H_

//
// Created by jyates on 3/25/19.
//

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "patterns/Command.h"

#include <memory>

class Metadata {
public:
    explicit Metadata(int some = 0): m_data(some) {}
    virtual ~Metadata() = default;

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
    ~SpecificData() override = default;

    int getSomeData() override {
        return m_data;
    }
};

class SomeCommand: public Command<SpecificData> {
public:
    SomeCommand() : val(5) {}
    ~SomeCommand() override = default;

    void execute() override {
        em_commandData.addData(val);
    }

private:
    int val;
};

class AnotherCommand: public Command<SpecificData> {
public:
    AnotherCommand() : val(10) {}
    ~AnotherCommand() override = default;

    void execute() override {
        em_commandData.addData(val);
    }

private:
    int val;
};

TEST(CommandTest, DifferentCommands) { // NOLINT
    std::vector<std::shared_ptr<Command<SpecificData>>> commandList;

    std::shared_ptr<SomeCommand> command = std::make_shared<SomeCommand>();
    commandList.push_back(command);

    std::shared_ptr<AnotherCommand> anotherCommand = std::make_shared<AnotherCommand>();
    commandList.push_back(anotherCommand);

    for (auto&& it: commandList) {
        it->execute();
    }

    EXPECT_NE(command->em_commandData.getSomeData(),
            anotherCommand->em_commandData.getSomeData());
}

int main(int argc, char** argv) {
    // Always required for gtest, which handles argument parsing.
    ::testing::InitGoogleMock(&argc, argv);

    // Run ALL tests found in this file (or in included headers).
    return RUN_ALL_TESTS();
}

/*
 * Test_Decorator.h
 *
 *  Created on: Jun 5, 2017
 *      Author: jyates
 */

#ifndef TESTING_PATTERNS_TEST_DECORATOR_H_
#define TESTING_PATTERNS_TEST_DECORATOR_H_

#include <sstream>
#include <cxxtest/TestSuite.h>

#include "../../Types/StandardDefines.h"

#include "../../Patterns/Decorator.h"

class MarshmallowDecorator : public Decorator<std::string> {
public:
    MarshmallowDecorator() {
        m_description = "Marshmallow Decorator";
    }

    MarshmallowDecorator(std::unique_ptr<Decorator<std::string>> decorator) :
        Decorator<std::string>(std::move(decorator)) {
        m_description = "Marshmallow Decorator";
    }

    ~MarshmallowDecorator() {}

private:
    virtual void processDecoration(std::string& decoratee) {
        decoratee.append("\tadding marshmallows...\n");
    }
};

class CreamDecorator : public Decorator<std::string> {
public:
    CreamDecorator() {
        m_description = "Cream Decorator";
    }

    CreamDecorator(std::unique_ptr<Decorator<std::string>> decorator) :
        Decorator<std::string>(std::move(decorator)) {
        m_description = "Cream Decorator";
    }

    ~CreamDecorator() {}

private:
    virtual void processDecoration(std::string& decoratee) {
        decoratee.append("\tadding cream...\n");
    }
};

class Coffee {
public:
    Coffee() : m_coffee(nullptr) {}
    ~Coffee() {}

    void addCoffeeTopping(std::unique_ptr<Decorator<std::string>> decorator) {
        if (decorator == nullptr) {
            throw std::runtime_error("current state is a nullptr");
        }
        if (m_coffee != nullptr) {
            m_coffee->addDecoration(std::move(decorator));
        } else {
            m_coffee = std::move(decorator);
        }
    }

    int finalizeCoffee(std::string& decoratee) {
        if (m_coffee == nullptr) {
            throw std::runtime_error("decorator member is a nullptr");
        }
        decoratee.append("\nCoffee description:\n");
        return m_coffee->processDecorations(decoratee);
    }

private:
    std::unique_ptr<Decorator<std::string>> m_coffee;
};

class Test_Decorator: public CxxTest::TestSuite {
public:
    void setUp   () { }
    void tearDown() { }

    void testDecoratorConstructor() {
        Coffee someCoffee;
        someCoffee.addCoffeeTopping(
                std::make_unique<CreamDecorator>(
                    std::make_unique<MarshmallowDecorator>()));
        std::string coffeeDecoratee;
        TS_ASSERT_EQUALS(someCoffee.finalizeCoffee(coffeeDecoratee), 2);
        TS_TRACE(coffeeDecoratee.c_str());
    }

    void testDecoratorConstructorDeep() {
        Coffee someCoffee;
        someCoffee.addCoffeeTopping(
                std::make_unique<CreamDecorator>(
                    std::make_unique<MarshmallowDecorator>(
                        std::make_unique<MarshmallowDecorator>(
                                std::make_unique<MarshmallowDecorator>()))));
        std::string coffeeDecoratee;
        TS_ASSERT_EQUALS(someCoffee.finalizeCoffee(coffeeDecoratee), 4);
        TS_TRACE(coffeeDecoratee.c_str());
    }

    void testDecoratorAdder() {
        Coffee someCoffee;
        someCoffee.addCoffeeTopping(std::make_unique<CreamDecorator>());
        someCoffee.addCoffeeTopping(std::make_unique<MarshmallowDecorator>());
        std::string coffeeDecoratee;
        TS_ASSERT_EQUALS(someCoffee.finalizeCoffee(coffeeDecoratee), 2);
        TS_TRACE(coffeeDecoratee.c_str());
    }

    void testDecoratorAdderDeep() {
        Coffee someCoffee;
        someCoffee.addCoffeeTopping(std::make_unique<CreamDecorator>());
        someCoffee.addCoffeeTopping(std::make_unique<MarshmallowDecorator>());
        someCoffee.addCoffeeTopping(std::make_unique<MarshmallowDecorator>());
        someCoffee.addCoffeeTopping(std::make_unique<MarshmallowDecorator>());
        std::string coffeeDecoratee;
        TS_ASSERT_EQUALS(someCoffee.finalizeCoffee(coffeeDecoratee), 4);
        TS_TRACE(coffeeDecoratee.c_str());
    }

private:

};

#endif // TESTING_PATTERNS_TEST_DECORATOR_H_

//
// Created by jyates on 3/29/19.
//

#include <string>
#include <memory>

#include "gmock/gmock.h"

#include "patterns/Decorator.h"

#include "StandardDefines.h"

/*
 * This mainly serves as an example of how to use the Decorator class (along
 * with the decorator pattern in general).
 */

class MarshmallowDecorator : public Decorator<std::string> {
public:
    MarshmallowDecorator() {
        m_description = "Marshmallow Decorator";
    }

    explicit MarshmallowDecorator(std::unique_ptr<Decorator<std::string>> decorator) :
            Decorator<std::string>(std::move(decorator)) {
        m_description = "Marshmallow Decorator";
    }

    ~MarshmallowDecorator() override = default;

private:
    void processDecoration(std::string& decoratee) override {
        decoratee.append("\tadding marshmallows...\n");
    }
};

class CreamDecorator : public Decorator<std::string> {
public:
    CreamDecorator() {
        m_description = "Cream Decorator";
    }

    explicit CreamDecorator(std::unique_ptr<Decorator<std::string>> decorator) :
            Decorator<std::string>(std::move(decorator)) {
        m_description = "Cream Decorator";
    }

    ~CreamDecorator() override = default;

private:
    void processDecoration(std::string& decoratee) override {
        decoratee.append("\tadding cream...\n");
    }
};

class Coffee {
public:
    Coffee() : m_coffee(nullptr) {}
    virtual ~Coffee() final = default;

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

TEST(DecoratorTesting, DecoratorConstructor) { // NOLINT
    Coffee someCoffee;
    someCoffee.addCoffeeTopping(
            std::make_unique<CreamDecorator>(
                    std::make_unique<MarshmallowDecorator>()));
    std::string coffeeDecoratee;
    EXPECT_EQ(someCoffee.finalizeCoffee(coffeeDecoratee), 2);
}

TEST(DecoratorTesting, DecoratorConstructorDeep) { // NOLINT
    Coffee someCoffee;
    someCoffee.addCoffeeTopping(
            std::make_unique<CreamDecorator>(
                    std::make_unique<MarshmallowDecorator>(
                            std::make_unique<MarshmallowDecorator>(
                                    std::make_unique<MarshmallowDecorator>()))));
    std::string coffeeDecoratee;
    EXPECT_EQ(someCoffee.finalizeCoffee(coffeeDecoratee), 4);
}

TEST(DecoratorTesting, DecoratorAdder) { // NOLINT
    Coffee someCoffee;
    someCoffee.addCoffeeTopping(std::make_unique<CreamDecorator>());
    someCoffee.addCoffeeTopping(std::make_unique<MarshmallowDecorator>());
    std::string coffeeDecoratee;
    EXPECT_EQ(someCoffee.finalizeCoffee(coffeeDecoratee), 2);
}

TEST(DecoratorTesting, DecoratorAdderDeep) { // NOLINT
    Coffee someCoffee;
    someCoffee.addCoffeeTopping(std::make_unique<CreamDecorator>());
    someCoffee.addCoffeeTopping(std::make_unique<MarshmallowDecorator>());
    someCoffee.addCoffeeTopping(std::make_unique<MarshmallowDecorator>());
    someCoffee.addCoffeeTopping(std::make_unique<MarshmallowDecorator>());
    std::string coffeeDecoratee;
    EXPECT_EQ(someCoffee.finalizeCoffee(coffeeDecoratee), 4);
}

int main(int argc, char** argv) {
    // Always required for gtest, which handles argument parsing.
    ::testing::InitGoogleMock(&argc, argv);

    // Run ALL tests found in this file (or in included headers).
    return RUN_ALL_TESTS();
}

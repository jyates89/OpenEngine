//
// Created by jyates on 4/3/19.
//

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "StandardDefines.h"

#include "patterns/State.h"
#include "patterns/StateContext.h"


class Player {
};

class StatusEffect : public State<Player> {
public:
    std::string statusName;
};

class Poison : public StatusEffect {
public:
    std::string stateDescription() const override {
        return "Poisoned";
    }

    void stateStarting(std::shared_ptr<Player> player) override {
        // Print "You have been poisoned, you are losing health!
    }

    void handleStateAction(std::shared_ptr<Player> player) override {
        // Print and reduce health... DOT!
    }

    void stateEnding(std::shared_ptr<Player> player) override {
        // Print "You have been cured of poison!"
    }
};

class Regeneration : public StatusEffect {
    std::string stateDescription() const override {
        return "Regenerating Health";
    }
};



TEST(StateTesting, OnState) { // NOLINT
    StateContext<Player> stateContext;

    std::shared_ptr<Player> player = std::make_shared<Player>(new Player);

    std::unique_ptr<Poison> poisonEffect = std::make_unique<Poison>(new Poison());
}

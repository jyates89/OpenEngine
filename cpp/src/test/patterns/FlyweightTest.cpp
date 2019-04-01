//
// Created by jyates on 3/29/19.

#include <string>
#include <vector>

#include "gmock/gmock.h"

#include "patterns/Flyweight.h"
#include "patterns/FlyweightFactory.h"

#include "StandardDefines.h"

// Position of the texture in a 2D world.
class Position {
public:
    int xPos;
    int yPos;

    Position(int x, int y) : xPos(x), yPos(y) {}
};

// Texture would be intrinsic to the flyweight; being reused in multiple
// spots throughout the rendered scene.
class Texture {
public:
    std::string textureName;
    std::vector<Position> positions;

    explicit Texture(std::string textureName)
            : textureName(std::move(textureName)) {}

    void updateState(Position position) {
        positions.push_back(position);
    }

    const std::vector<Position> getPositions() const {
        return positions;
    }

};


TEST(FlyweightTest, TextureFlyweightTest) { // NOLINT
    FlyweightFactory<Texture, Position> flyweightFactory;
    auto fw = flyweightFactory.getInstance(UniqueID(), "TestTexture.tga");
    fw->updateState(Position(0, 0));
    ASSERT_EQ(fw->intrinsic()->getPositions().size(), 1);
    ASSERT_EQ(fw->intrinsic()->textureName, "TestTexture.tga");
}

int main(int argc, char** argv) {
    // Always required for gtest, which handles argument parsing.
    ::testing::InitGoogleMock(&argc, argv);

    // Run ALL tests found in this file (or in included headers).
    return RUN_ALL_TESTS();
}

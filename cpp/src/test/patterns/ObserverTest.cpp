//
// Created by jyates on 3/25/19.
//

#include "gmock/gmock.h"
#include "gtest/gtest.h"


int main(int argc, char** argv) {
    // Always required for gtest, which handles argument parsing.
    ::testing::InitGoogleMock(&argc, argv);

    // Run ALL tests found in this file (or in included headers).
    return RUN_ALL_TESTS();
}

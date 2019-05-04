//
// Created by jyates on 4/27/19.
//

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "net/BroadcastListener.h"
#include "net/BroadcastSender.h"

#include "net/TCPServer.h"
#include "net/TCPClient.h"

#include "net/UDPListener.h"
#include "net/UDPSender.h"

#include "net/UnixServer.h"
#include "net/UnixClient.h"


TEST(SocketTest, SocketTest) { // NOLINT

}

int main(int argc, char** argv) {
    // Always required for gtest, which handles argument parsing.
    ::testing::InitGoogleMock(&argc, argv);

    // Run ALL tests found in this file (or in included headers).
    return RUN_ALL_TESTS();
}

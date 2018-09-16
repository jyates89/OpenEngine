//
// Created by jyates on 9/14/18.
//

#include <vector>
#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

// Sockets are a good candidate for mocking.
class SocketInterface {
public:
    SocketInterface() = default;
    virtual ~SocketInterface() = default;

    virtual int send(const std::vector<char>& buffer) = 0;
};


class SocketUser {
public:
    SocketUser() = default;
    ~SocketUser() = default;

    // Socket can be any type; TCP or UDP
    int useSocket(const std::shared_ptr<SocketInterface>& socket, const std::vector<char>& buffer) {
        if (socket->send(buffer) != buffer.size()) {
            return -1;
        } else {
            return 0;
        }
    }
};

class SocketWrapperMock : public SocketInterface {
public:
    MOCK_METHOD1(send, int(const std::vector<char>&));
};

TEST(SocketTest, CanUseSocketSuccess) { // NOLINT
    std::shared_ptr<SocketWrapperMock> socket = std::make_shared<SocketWrapperMock>();

    std::vector<char> buffer = {1, 2, 3, 4};

    EXPECT_CALL(*socket, send(::testing::_))
        .Times(::testing::AtLeast(1))
        .WillOnce(::testing::Return(buffer.size()));

    SocketUser socketUser;
    EXPECT_EQ(socketUser.useSocket(socket, buffer), 0);
}

TEST(SocketTest, CanUseSocketFailure) { // NOLINT
    std::shared_ptr<SocketWrapperMock> socket = std::make_shared<SocketWrapperMock>();

    std::vector<char> buffer = {1, 2, 3, 4};

    EXPECT_CALL(*socket, send(::testing::_))
            .Times(::testing::AtLeast(1))
            .WillOnce(::testing::Return(0));

    SocketUser socketUser;
    EXPECT_EQ(socketUser.useSocket(socket, buffer), -1);
}

int main(int argc, char** argv) {
    // Always required for gtest, which handles argument parsing.
    ::testing::InitGoogleMock(&argc, argv);

    // Run ALL tests found in this file (or in included headers).
    return RUN_ALL_TESTS();
}

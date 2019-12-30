//
// Created by jyates on 4/27/19.
//

#ifndef OPENENGINE_SOCKET_H
#define OPENENGINE_SOCKET_H

#include <memory>

extern "C" {
#include <unistd.h>
};

#include "serialization/Serializable.h"
#include "serialization/Deserializable.h"

#include "builders/HintBuilder.h"

namespace OE {

class Socket {
protected:
    const int socketDescriptor;

    explicit Socket(int socketDescriptor);

public:
    virtual ~Socket() = default;

    ssize_t send(std::unique_ptr<Serializable> serializable);
    virtual ssize_t send(
            std::unique_ptr<Serializable> serializable,
            int flags) = 0;

    ssize_t recv(std::unique_ptr<Deserializable> deserializable);
    virtual ssize_t recv(
            std::unique_ptr<Deserializable> deserializable,
            int flags) = 0;

    static HintBuilder hintBuilder();
};

Socket::Socket(int socketDescriptor) :
        socketDescriptor(socketDescriptor) {
}

ssize_t Socket::send(std::unique_ptr<Serializable> serializable) {
    return send(std::move(serializable), 0);
}

ssize_t Socket::recv(std::unique_ptr<Deserializable> deserializable) {
    return recv(std::move(deserializable), 0);
}

HintBuilder Socket::hintBuilder() {
    return { };
}

}
#endif //OPENENGINE_SOCKET_H

//
// Created by jyates on 6/1/19.
//

#include "net/TCPSocket.h"

namespace OE {

TCPSocket::TCPSocket(int socketDescriptor) :
        Socket(socketDescriptor) {

}

ssize_t TCPSocket::send(
        std::unique_ptr<Serializable> serializable, int flags) {
    return 0;
}

ssize_t TCPSocket::recv(
        std::unique_ptr<Deserializable> deserializable, int flags) {
    return 0;
}

}

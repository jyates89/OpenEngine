//
// Created by jyates on 6/1/19.
//

#include <netdb.h>
#include <sys/types.h>

namespace OE {

struct addrinfo fillIPV4TCPBind() {
    struct addrinfo hints = { 0 };
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    return hints;
}

struct addrinfo fillIPV4TCPConnect() {
    struct addrinfo hints = { 0 };
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    return hints;
}

struct addrinfo fillIPV4UDP() {
    struct addrinfo hints = {0};

}
}

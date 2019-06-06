//
// Created by jyates on 6/4/19.
//

#ifndef OPENENGINE_HINTBUILDER_H
#define OPENENGINE_HINTBUILDER_H

extern "C" {
#include <sys/types.h>
#include <netdb.h>
};

namespace OE {

class HintBuilder {
    struct addrinfo hints;

public:
    HintBuilder() : hints({0}) {
        // defaults
        hints.ai_family = AF_UNSPEC;
    }

    struct addrinfo build() {
        return hints;
    }

    HintBuilder withTCP() {
        hints.ai_socktype = SOCK_STREAM;
        return *this;
    }

    HintBuilder withUDP() {
        hints.ai_socktype = SOCK_DGRAM;
        return *this;
    }

    HintBuilder asServer() {
        hints.ai_flags |= AI_PASSIVE;
        return *this;
    }

};

}

#endif //OPENENGINE_HINTBUILDER_H

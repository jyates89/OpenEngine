//
// Created by jyates on 6/4/19.
//

#ifndef OPENENGINE_RECVFLAGBUILDER_H
#define OPENENGINE_RECVFLAGBUILDER_H

extern "C" {
#include <sys/types.h>
#include <sys/socket.h>
};

class RecvFlagBuilder {
    int flags;

public:
    RecvFlagBuilder() : flags(0) {}

    int build() {
        return flags;
    }

    RecvFlagBuilder disableBlocking() {
        flags |= MSG_DONTWAIT;
        return *this;
    }

    RecvFlagBuilder disableRouting() {
        flags |= MSG_DONTROUTE;
        return *this;
    }

    RecvFlagBuilder enablePeeking() {
        flags |= MSG_PEEK;
        return *this;
    }

    RecvFlagBuilder enableOutofBand() {
        flags |= MSG_OOB;
        return *this;
    }

    // For raw, UDP, and UNIX. Return real length
    // of packet or datagram, even when that length
    // is longer than passed in buffer.
    RecvFlagBuilder disableTruncating() {
        flags |= MSG_TRUNC;
        return *this;
    }

    // No effect for UDP.
    RecvFlagBuilder expectEntireMessage() {
        flags |= MSG_WAITALL;
        return *this;
    }
};

#endif //OPENENGINE_RECVFLAGBUILDER_H

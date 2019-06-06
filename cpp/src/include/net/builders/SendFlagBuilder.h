//
// Created by jyates on 6/4/19.
//

#ifndef OPENENGINE_SOCKETFLAGBUILDER_H
#define OPENENGINE_SOCKETFLAGBUILDER_H

extern "C" {
#include <sys/types.h>
#include <sys/socket.h>
};

namespace OE {

class SendFlagBuilder {
    int flags;

public:
    SendFlagBuilder() : flags(0) { }

    int build() {
        return flags;
    }

    // Valid only for raw and datagram.
    SendFlagBuilder confirmMessages() {
        flags |= MSG_CONFIRM;
        return *this;
    }

    SendFlagBuilder disableBlocking() {
        flags |= MSG_DONTWAIT;
        return *this;
    }

    // Don't send the packet yet. Supported
    // for TCP and UDP.
    SendFlagBuilder expectMoreData() {
        flags |= MSG_MORE;
        return *this;
    }

    SendFlagBuilder ignorePipeSignal() {
        flags |= MSG_NOSIGNAL;
        return *this;
    }

    SendFlagBuilder disableRouting() {
        flags |= MSG_DONTROUTE;
        return *this;
    }

    SendFlagBuilder enableOutofBand() {
        flags |= MSG_OOB;
        return *this;
    }
};

}

#endif //OPENENGINE_SOCKETFLAGBUILDER_H

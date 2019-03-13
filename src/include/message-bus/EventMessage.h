//
// Created by jyates on 2/15/19.
//

#ifndef OPENENGINE_EVENTMESSAGE_H
#define OPENENGINE_EVENTMESSAGE_H

#include <climits>

#include "EventMessage.h"
#include "EventMessageHeader.h"

class EventMessage {
public:
    enum class EventType {
        STARTUP_NOTICE,
        SHUTDOWN_NOTICE,
    };


protected:


private:

};

#endif //OPENENGINE_EVENTMESSAGE_H

//
// Created by jyates on 2/15/19.
//

#ifndef OPENENGINE_EVENTMESSAGEHANDLER_H
#define OPENENGINE_EVENTMESSAGEHANDLER_H

#include <unordered_map>
#include <vector>
#include <functional>

#include "EventMessage.h"

template<enum T>
class EventMessageHandler {
    std::unordered_map<EventMessage::EventType,
        std::vector<std::function<void(void)>>> registrantMap;
public:
    int registerHandler(EventMessage::EventType messageType,
                        const std::function<void()>& callback);
    void removeHandler(EventMessage::EventType eventType,
                       int handlerIdentifier);
};

#endif //OPENENGINE_EVENTMESSAGEHANDLER_H

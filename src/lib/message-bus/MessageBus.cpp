//
// Created by jyates on 2/13/19.
//

#include "message-bus/MessageBus.h"
#include "message-bus/MessageType.h"

int MessageBus::registerHandler(EventMessage::EventType eventType,
        const std::function<void()>& callback) {
}

void MessageBus::removeHandler(EventMessage::EventType eventType,
        int handlerIdentifier) {

}


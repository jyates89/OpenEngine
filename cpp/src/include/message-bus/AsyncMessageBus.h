//
// Created by jyates on 2/15/19.
//

#ifndef OPENENGINE_ASYNCMESSAGEBUS_H
#define OPENENGINE_ASYNCMESSAGEBUS_H

#include "MessageBus.h"

class AsyncMessageBus : public MessageBus {
    std::queue<std::shared_ptr<MessageType>> messageQueue;

public:
    AsyncMessageBus() = default;
    virtual ~AsyncMessageBus() = default;
};

#endif //OPENENGINE_ASYNCMESSAGEBUS_H

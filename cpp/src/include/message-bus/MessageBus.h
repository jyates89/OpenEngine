//
// Created by jyates on 2/13/19.
//

#ifndef OPENENGINE_BUS_H
#define OPENENGINE_BUS_H

#include <vector>
#include <unordered_map>
#include <utility>
#include <functional>
#include <queue>
#include <memory>

#include "MessageType.h"
#include "Enumerator.h"

// Base message bus; it's up the the sub classes to select a type of queue
// and how to handle it.
class MessageBus {
    class HandlerStore {
    public:
        std::uint32_t identifier;
        std::function<void(std::unique_ptr<MessageType>)> handler;
    };

    std::unordered_map<UniqueID, std::vector<HandlerStore>> handlerMap;

protected:
    MessageBus() = default;

public:
    virtual ~MessageBus() = default;

    // return the handle ID to save for removing from registrant list
    uint32_t registerHandler(UniqueID messageID,
            std::function<void(std::unique_ptr<MessageType>)> handler);

    void removeHandler(UniqueID messageID, std::uint32_t handlerIdentifier);

};

#endif //OPENENGINE_BUS_H

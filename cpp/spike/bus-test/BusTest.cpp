//
// Created by jyates on 2/13/19.
//

#include "message-bus/AsyncMessageBus.h"

#include "BusMessage.h"

#include "Logging.h"

int main(int argc, char** argv) {

    BusMessage busMessage;

    AsyncMessageBus messageBus;
    messageBus.registerMessageType(busMessage.identifier());

    std::uint32_t identifier = messageBus.registerHandler(busMessage.identifier(),
            [](std::unique_ptr<MessageType>){});

    messageBus.removeHandler(busMessage.identifier(), identifier);

}

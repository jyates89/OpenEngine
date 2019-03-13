//
// Created by jyates on 2/15/19.
//

#include "messagebus/EventMessageHandler.h"

template<typename T>
int EventMessageHandler<T>::registerHandler(EventMessage::EventType eventType,
        const std::function<void()>& callback) {
    auto it = registrantMap.find(eventType);
    if (it != registrantMap.end()) {
        it->second.push_back(callback);
        return it->second.size() - 1;
    }
    std::vector<std::function<void()>> callbacks;
    callbacks.push_back(callback);
    registrantMap.insert(std::make_pair(eventType, callbacks));
    return 0;

}

template<typename T>
void EventMessageHandler<T>::removeHandler(EventMessage::EventType eventType,
        int handlerIdentifier) {
    auto it = registrantMap.find(eventType);
    if (it != registrantMap.end()) {
        it->second.erase(it->second.begin() + handlerIdentifier);
    }
}

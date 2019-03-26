/*
 * Observable.cpp
 *
 *  Created on: May 19, 2017
 *      Author: jyates
 */

#include <stdexcept>
#include <utility>

#include "patterns/Observable.h"

Observable::Observable() {}

Observable::~Observable() {}

void Observable::subscribeObserver(std::shared_ptr<Observer> observer) {
    if (m_observers.find(observer->getIdentifier()) == m_observers.end()) {
        std::pair<UniqueID, std::shared_ptr<Observer>> newPair;
        m_observers.insert(std::make_pair(observer->getIdentifier(), observer));
    } else {
        throw std::invalid_argument("object already exists");
    }
}

void Observable::notifySubscribers() {
    auto it = m_observers.begin();
    while (it != m_observers.end()) {
        it->second->notify();
        ++it;
    }
}

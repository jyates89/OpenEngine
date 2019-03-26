/*
 * Observable.h
 *
 *  Created on: May 19, 2017
 *      Author: jyates
 */

#ifndef PATTERNS_OBSERVABLE_H_
#define PATTERNS_OBSERVABLE_H_

#include "UniqueID.h"

#include "Observer.h"

#include <memory>
#include <unordered_map>

class Observable {
public:
    Observable();
    virtual ~Observable();

    void subscribeObserver(std::shared_ptr<Observer> observer);
    void notifySubscribers();

private:
    std::unordered_map<UniqueID, std::shared_ptr<Observer>> m_observers;
};

#endif /* PATTERNS_OBSERVABLE_H_ */

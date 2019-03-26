/*
 * Observer.h
 *
 *  Created on: May 19, 2017
 *      Author: jyates
 */

#ifndef PATTERNS_OBSERVER_H_
#define PATTERNS_OBSERVER_H_

#include "UniqueID.h"

class Observer {
    friend class Observable;

public:
    Observer();
    virtual ~Observer();

    virtual int notify() = 0;

    const UniqueID& getIdentifier() const;

private:
    UniqueID m_identifier;

};

#endif /* PATTERNS_OBSERVER_H_ */

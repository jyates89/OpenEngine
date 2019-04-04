/*
 * State.h
 *
 *  Created on: May 27, 2017
 *      Author: jyates
 */

#ifndef PATTERNS_STATE_H_
#define PATTERNS_STATE_H_

#include <string>
#include <memory>

template<class StatefulType>
class State {
public:
    virtual std::string stateDescription() const = 0;

    virtual void stateStarting(std::shared_ptr<StatefulType> statefulType) = 0;

    virtual void handleStateAction(std::shared_ptr<StatefulType> statefulType) = 0;

    virtual void stateEnding(std::shared_ptr<StatefulType> statefulType) = 0;
};

#endif /* PATTERNS_STATE_H_ */

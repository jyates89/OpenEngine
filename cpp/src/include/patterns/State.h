/*
 * State.h
 *
 *  Created on: May 27, 2017
 *      Author: jyates
 */

#ifndef PATTERNS_STATE_H_
#define PATTERNS_STATE_H_

#include <string>

template<class StateData>
class State {
public:
    State() {}
    virtual ~State() {}

    virtual std::string stateDescription() const = 0;

    virtual void stateStarting() = 0;

    virtual void handleStateAction() = 0;

    virtual void stateEnding() = 0;

    StateData& getStateData();

protected:
    StateData m_stateDataObject;
};

template<class StateData>
inline StateData& State<StateData>::getStateData() {
    return m_stateDataObject;
}

#endif /* PATTERNS_STATE_H_ */

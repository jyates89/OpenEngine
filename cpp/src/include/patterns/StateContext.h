/*
 * StateContext.h
 *
 *  Created on: May 27, 2017
 *      Author: jyates
 */

#ifndef PATTERNS_STATECONTEXT_H_
#define PATTERNS_STATECONTEXT_H_

#include <memory>
#include <string>
#include <deque>
#include "Enumerator.h"

#include "State.h"

template<typename StateType, StateType head, StateType... states>
class StateContext {
    static_assert(std::is_enum<StateType>::value,
                  "StateType must be an enumeration type!");
public:
    using State_t = std::reference_wrapper<State<StateType, states...>>;

private:
    std::string contextDescription;

    State_t currentState;

    std::deque<State_t> stateHistory;

public:
    explicit StateContext(std::string contextDescription);
    virtual ~StateContext() = default;

    virtual void stateChange(State_t state);

    void undoChange();
    void redoChange();

    std::string getContextDescription() const;

    const State_t& getCurrentState() const;

};

template<typename StateType, StateType head, StateType... states>
inline void StateContext<StateType, head, states...>::stateChange(
        State_t state) {
    if (currentState != nullptr) {
        currentState->onEnd();
        stateHistory.push_back(std::move(state));
    }
    currentState = std::move(state);
    currentState->onStart();
}

template<typename StateType, StateType head, StateType... states>
const typename StateContext<StateType, head, states...>::State_t&
    StateContext<StateType, head, states...>::getCurrentState() const {
        return currentState;
}

template<typename StateType, StateType head, StateType... states>
void StateContext<StateType, head, states...>::undoChange() {
    if (currentState != nullptr) {
        currentState->onRevert();
        stateHistory.push_front(std::move(currentState));
    }
    if (stateHistory.size() > 0) {
        currentState = std::move(stateHistory.back());
        stateHistory.pop_back();
        currentState->onStart();
    }
}

template<typename StateType, StateType head, StateType... states>
void StateContext<StateType, head, states...>::redoChange() {
    currentState->onEnd();
    stateHistory.push_back(std::move(currentState));
    currentState = std::move(stateHistory.front());
    stateHistory.pop_front();
    currentState->onStart();

}

template<typename StateType, StateType head, StateType... states>
StateContext<StateType, head, states...>::StateContext(std::string contextDescription) {
    this->contextDescription = contextDescription;
}

template<typename StateType, StateType head, StateType... states>
std::string StateContext<StateType, head, states...>::getContextDescription() const {
    return contextDescription;
}

#endif /* PATTERNS_STATECONTEXT_H_ */

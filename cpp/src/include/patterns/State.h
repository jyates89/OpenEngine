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

template<typename StateType, StateType head, StateType... states>
class StateContext;

template<typename StateType, StateType head, StateType... states>
class State {
protected:

    std::string stateDescription;

    // Back reference to context allows state to change itself.
    std::shared_ptr<StateContext<StateType, head, states...>> stateContext;

public:
    State() = delete;

    explicit State(std::shared_ptr<StateContext<StateType, states...>> stateContext,
            std::string description = "");
    virtual ~State() = default;

    std::string getDescription();

    virtual void onStart() = 0;

    virtual void onRevert();

    virtual void onEnd() = 0;
};

template<typename StateType, StateType... states>
State<StateType, states...>::State(std::shared_ptr<StateContext<StateType, states...>> stateContext,
        std::string description) {
    this->stateContext = std::move(stateContext);
    this->stateDescription = std::move(description);
}

template<typename StateType, StateType... states>
std::string State<StateType, states...>::getDescription() {
    return stateDescription;
}

template<typename StateType, StateType... states>
void State<StateType, states...>::onRevert() {
    // Call onEnd() by default, but this offers the potential to define
    // a custom step used for reverting a state.
    onEnd();
}

#endif /* PATTERNS_STATE_H_ */

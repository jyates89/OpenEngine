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
#include <stack>

#include "../Types/StandardDefines.h"

template<class StateData>
class StateContext {
public:
    StateContext();
    virtual ~StateContext();

    void stateChange(std::unique_ptr<State<StateData>> state);

    void undoStateChange();
    void redoStateChange();

    void executeCurrentStateHandler();

    std::string currentStateDescription() const;

protected:
    std::unique_ptr<State<StateData>> m_currentState;

private:
    std::stack<std::unique_ptr<State<StateData>>> m_stateHistory;
    std::stack<std::unique_ptr<State<StateData>>> m_undoHistory;
};

template<class StateData>
inline StateContext<StateData>::StateContext() {
}

template<class StateData>
inline StateContext<StateData>::~StateContext() {
}

template<class StateData>
inline void StateContext<StateData>::stateChange(
        std::unique_ptr<State<StateData>> state) {
    if (state == nullptr) {
        throw std::invalid_argument("invalid arguments: nullptr");
    }
    if (m_currentState != nullptr) {
        m_currentState->stateEnding();
        m_stateHistory.push(std::move(m_currentState));
    }
    m_currentState = std::move(state);
    m_currentState->stateStarting();
}

template<class StateData>
inline void StateContext<StateData>::undoStateChange() {
    if (m_stateHistory.empty()) {
        return;
    }
    if (m_currentState != nullptr) {
        m_undoHistory.push(std::move(m_currentState));
    }
    stateChange(std::move(m_stateHistory.top()));
    m_stateHistory.pop();
}

template<class StateData>
inline void StateContext<StateData>::redoStateChange() {
    if (m_undoHistory.empty()) {
        return;
    }
    if (m_currentState != nullptr) {
        m_stateHistory.push(std::move(m_currentState));
    }
    stateChange(std::move(m_undoHistory.top()));
    m_undoHistory.pop();
}

template<class StateData>
inline void StateContext<StateData>::executeCurrentStateHandler() {
    if (m_currentState == nullptr) {
        throw std::runtime_error("current state is a nullptr");
    }
    m_currentState->handleStateAction();
}

template<class StateData>
inline std::string StateContext<StateData>::currentStateDescription() const {
    return m_currentState->stateDescription();
}

#endif /* PATTERNS_STATECONTEXT_H_ */

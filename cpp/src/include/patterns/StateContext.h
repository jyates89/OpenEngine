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

template<class StatefulType>
class StateContext {
public:
    StateContext() = default;
    virtual ~StateContext() = default;

    void stateChange(std::shared_ptr<StatefulType> statefulType,
            std::unique_ptr<State<StatefulType>> state);

    void undoStateChange();
    void redoStateChange();

    void executeCurrentStateHandler();

    std::string currentStateDescription() const;

protected:
    std::shared_ptr<StatefulType> m_lastApplication;
    std::unique_ptr<State<StatefulType>> m_currentState;

private:
    std::stack<std::unique_ptr<State<StatefulType>>> m_stateHistory;
    std::stack<std::unique_ptr<State<StatefulType>>> m_undoHistory;
};

template<class StatefulType>
inline void StateContext<StatefulType>::stateChange(
        std::shared_ptr<StatefulType> statefulType,
        std::unique_ptr<State<StatefulType>> state) {
    if (state == nullptr) {
        throw std::invalid_argument("invalid arguments: nullptr");
    }
    if (m_currentState != nullptr) {
        m_currentState->stateEnding();
        m_stateHistory.push(std::move(m_currentState));
    }
    m_currentState = std::move(state);
    m_currentState->stateStarting();
    m_lastApplication = statefulType;
}

template<class StatefulType>
inline void StateContext<StatefulType>::undoStateChange() {
    if (m_stateHistory.empty()) {
        return;
    }
    if (m_currentState != nullptr) {
        m_undoHistory.push(std::move(m_currentState));
    }
    stateChange(std::move(m_stateHistory.top()));
    m_stateHistory.pop();
}

template<class StatefulType>
inline void StateContext<StatefulType>::redoStateChange() {
    if (m_undoHistory.empty()) {
        return;
    }
    if (m_currentState != nullptr) {
        m_stateHistory.push(std::move(m_currentState));
    }
    stateChange(std::move(m_undoHistory.top()));
    m_undoHistory.pop();
}

template<class StatefulType>
inline void StateContext<StatefulType>::executeCurrentStateHandler() {
    if (m_currentState == nullptr) {
        throw std::runtime_error("current state is a nullptr");
    }
    m_currentState->handleStateAction();
}

template<class StatefulType>
inline std::string StateContext<StatefulType>::currentStateDescription() const {
    return m_currentState->stateDescription();
}

#endif /* PATTERNS_STATECONTEXT_H_ */

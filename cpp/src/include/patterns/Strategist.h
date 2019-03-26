/*
 * Strategist.h
 *
 *  Created on: May 30, 2017
 *      Author: jyates
 */

#ifndef PATTERNS_STRATEGIST_H_
#define PATTERNS_STRATEGIST_H_

#include <memory>
#include <array>
#include <string>

#include <utility>     // std::move
#include <stdexcept>   // exception support
#include <type_traits> // is_enum

#include "../Types/StandardDefines.h" // nullptr
#include "../Types/Enumerator.h"

#include "StrategyException.h"
#include "Strategy.h"

template<typename EnumType, EnumType head, EnumType... strategies>
class Strategist {
static_assert(std::is_enum<EnumType>::value,
        "EnumType must be an enumeration type!");
friend class Test_Strategy;
public:
    Strategist          ();
    virtual ~Strategist ();

    void executeCurrentStrategy();

    void assignStrategy   (EnumType newStrategyType,
                           std::unique_ptr<Strategy> newStrategy);

    std::unique_ptr<Strategy> unassignStrategy(EnumType existingStrategy);

    EnumType switchStrategy     (EnumType strategyChange);
    EnumType currentStrategyType() const;

private:
    static const std::string CURRENT_NULLPTR_ERR;
    static const std::string PASSED_NULLPTR_ERR;
    static const std::string SWITCH_NULLPTR_ERR;
    static const std::string IN_USE_ERR;
    static const std::string OVERWRITE_ERR;

    typedef Enumerator<EnumType, head, strategies...> Enumeration;

    std::unique_ptr<Strategy> m_currentStrategy;
    EnumType                  m_currentStrategyType;

    std::array<std::unique_ptr<Strategy>,
                Enumeration::count> m_availableStrategies;

};

template<typename EnumType, EnumType head, EnumType... strategies>
const std::string Strategist<EnumType, head, strategies...>::CURRENT_NULLPTR_ERR
    = "current strategy object is a nullptr";

template<typename EnumType, EnumType head, EnumType... strategies>
const std::string Strategist<EnumType, head, strategies...>::PASSED_NULLPTR_ERR
    = "strategy passed in as nullptr";

template<typename EnumType, EnumType head, EnumType... strategies>
const std::string Strategist<EnumType, head, strategies...>::SWITCH_NULLPTR_ERR
    = "attempted to switch to a strategy set to a nullptr";

template<typename EnumType, EnumType head, EnumType... strategies>
const std::string Strategist<EnumType, head, strategies...>::IN_USE_ERR
    = "cannot remove strategy that is in use";

template<typename EnumType, EnumType head, EnumType... strategies>
const std::string Strategist<EnumType, head, strategies...>::OVERWRITE_ERR
    = "cannot overwrite an existing strategy";

template<typename EnumType, EnumType head, EnumType... strategies>
inline Strategist<EnumType, head, strategies...>::Strategist() :
    m_currentStrategyType(head) {
}

template<typename EnumType, EnumType head, EnumType... strategies>
inline Strategist<EnumType, head, strategies...>::~Strategist() {
}

template<typename EnumType, EnumType head, EnumType... strategies>
inline void Strategist<EnumType, head, strategies...>::executeCurrentStrategy() {
    if (m_currentStrategy == nullptr) {
        throw std::runtime_error(CURRENT_NULLPTR_ERR);
    }
    m_currentStrategy->executeStrategy();
}

template<typename EnumType, EnumType head, EnumType... strategies>
inline void Strategist<EnumType, head, strategies...>::assignStrategy(
        EnumType newStrategyType, std::unique_ptr<Strategy> newStrategy) {
    if (newStrategy == nullptr) {
        throw std::invalid_argument(PASSED_NULLPTR_ERR);
    }
    unsigned long long index = Enumeration::convert(newStrategyType);
    if (m_availableStrategies[index] != nullptr) {
        throw StrategyException(std::move(newStrategy), OVERWRITE_ERR);
    }
    m_availableStrategies[index] = std::move(newStrategy);
}

template<typename EnumType, EnumType head, EnumType... strategies>
inline std::unique_ptr<Strategy> Strategist<EnumType, head, strategies...>::unassignStrategy(
        EnumType existingStrategy) {
    if (m_currentStrategyType == existingStrategy) {
        throw std::runtime_error(IN_USE_ERR);
    }
    unsigned long long index = Enumeration::convert(existingStrategy);
    return std::move(m_availableStrategies[index]);
}

template<typename EnumType, EnumType head, EnumType... strategies>
inline EnumType Strategist<EnumType, head, strategies...>::switchStrategy(
        EnumType strategyChange) {
    unsigned long long index = Enumeration::convert(strategyChange);
    if (m_availableStrategies[index] == nullptr) {
        throw std::runtime_error(SWITCH_NULLPTR_ERR);
    }
    EnumType oldStrategy = m_currentStrategyType;

    m_currentStrategyType = strategyChange;
    m_currentStrategy = std::move(m_availableStrategies[index]);

    return oldStrategy;
}

template<typename EnumType, EnumType head, EnumType... strategies>
inline EnumType Strategist<EnumType, head, strategies...>::currentStrategyType() const {
    return m_currentStrategyType;
}

#endif /* PATTERNS_STRATEGIST_H_ */

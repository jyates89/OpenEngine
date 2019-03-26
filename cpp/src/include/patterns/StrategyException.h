/*
 * StrategyException.h
 *
 *  Created on: Jul 3, 2017
 *      Author: jyates
 */

#ifndef PATTERNS_STRATEGYEXCEPTION_H_
#define PATTERNS_STRATEGYEXCEPTION_H_

#include <stdexcept>   // exception support

#include "Strategy.h"

class StrategyException : public std::runtime_error {
public:
    // Preserve the strategy we attempted to assign. This is
    //  thrown when the strategy we attempt to assign already
    //  exists. Since the strategy is a unique_ptr, and can
    //  only be moved, we save it in the thrown exception so
    //  that the caller can recover ownership of the strategy.
    std::unique_ptr<Strategy> em_thrownStrategy;

    StrategyException(
            std::unique_ptr<Strategy> strategy,
            const std::string& what) :
        std::runtime_error(what),
        em_thrownStrategy(std::move(strategy)) {
    }

    // We use a unique_ptr as a member of this exception type,
    //  so we must declare a move constructor and delete the
    //  copy constructor. By default, exceptions must allow
    //  themselves to be copied. However, we can get around this
    //  by specifying the move constructor (and deleting the
    //  copy constructor for good measure).
    StrategyException(StrategyException&& incoming) :
        std::runtime_error(incoming.what()) {
        if (this != &incoming) {
            em_thrownStrategy = std::move(incoming.em_thrownStrategy);
        }
    }
    StrategyException(const StrategyException& incoming) = delete;

    // When inheriting from the standard exceptions, we must make
    //  sure the destructor is declared as not throwing any
    //  exceptions. In our version of GCC, we use throw(). In later
    //  versions, we would use noexcept as the qualifier.
    ~StrategyException() throw() {}
};


#endif /* PATTERNS_STRATEGYEXCEPTION_H_ */

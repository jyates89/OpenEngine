/*
 * Decorator.h
 *
 *  Created on: May 19, 2017
 *      Author: jyates
 */

#ifndef PATTERNS_DECORATOR_H_
#define PATTERNS_DECORATOR_H_

#include <memory>
#include <string>

#include "../Types/StandardDefines.h"

template<class Decoratee>
class Decorator {
public:
    virtual ~Decorator();

    virtual void addDecoration(std::unique_ptr<Decorator<Decoratee>> decoration);

    int processDecorations(Decoratee& decoratee);

protected:
    std::string m_description;
    std::unique_ptr<Decorator<Decoratee>> m_nestedDecorator;

    Decorator();
    Decorator(std::unique_ptr<Decorator<Decoratee>> decorator);

private:
    virtual void processDecoration(Decoratee& decoratee) = 0;

};

template<class Decoratee>
inline Decorator<Decoratee>::~Decorator() {
}

template<class Decoratee>
inline void Decorator<Decoratee>::addDecoration(
        std::unique_ptr<Decorator<Decoratee>> decoration) {
    if (decoration == nullptr) {
        throw std::invalid_argument("invalid arguments: nullptr");
    }
    if (m_nestedDecorator == nullptr) {
        m_nestedDecorator = std::move(decoration);
    } else {
        m_nestedDecorator->addDecoration(std::move(decoration));
    }
}

template<class Decoratee>
inline int Decorator<Decoratee>::processDecorations(Decoratee& decoratee) {
    processDecoration(decoratee);
    if (m_nestedDecorator != nullptr) {
        return 1 + m_nestedDecorator->processDecorations(decoratee);
    }
    return 1;
}

template<class Decoratee>
inline Decorator<Decoratee>::Decorator() :
        m_description("default"),
        m_nestedDecorator(nullptr) {
}

template<class Decoratee>
inline Decorator<Decoratee>::Decorator(
        std::unique_ptr<Decorator<Decoratee>> decoration) :
            m_nestedDecorator(nullptr) {
    if (decoration == nullptr) {
        throw std::invalid_argument("invalid arguments: nullptr");
    }
    m_nestedDecorator = std::move(decoration);
}

#endif /* PATTERNS_DECORATOR_H_ */

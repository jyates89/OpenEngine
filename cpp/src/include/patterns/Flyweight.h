/*
 * Flyweight.h
 *
 *  Created on: May 27, 2017
 *      Author: jyates
 */

#ifndef PATTERNS_FLYWEIGHT_H_
#define PATTERNS_FLYWEIGHT_H_

#include <memory>

#include "../Types/UniqueID.h"

template<class Intrinsic, class Extrinsic>
class Flyweight {
public:
    UniqueID em_identifier;

    Flyweight();
    virtual ~Flyweight();

    Flyweight(const Flyweight& right) = delete;

    Flyweight& operator =(const Flyweight& right);

    virtual void calculateState(Extrinsic extrinsic) = 0;

protected:
    std::unique_ptr<Intrinsic> m_intrinsicState;

private:
    Intrinsic validateIntrinsic() { return Intrinsic(); }
};

template<class Intrinsic, class Extrinsic>
inline Flyweight<Intrinsic, Extrinsic>::~Flyweight() {
}

template<class Intrinsic, class Extrinsic>
inline Flyweight<Intrinsic, Extrinsic>::Flyweight() :
        m_intrinsicState(new Intrinsic) {
}

template<class Intrinsic, class Extrinsic>
inline Flyweight<Intrinsic, Extrinsic>& Flyweight<Intrinsic, Extrinsic>::operator =(
        const Flyweight& right) {
    if (right != *this) {
        em_identifier = right.em_identifier;
        m_intrinsicState = std::move(right.m_intrinsicState);
    }
    return *this;
}

#endif /* PATTERNS_FLYWEIGHT_H_ */

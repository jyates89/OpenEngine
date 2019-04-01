/*
 * Flyweight.h
 *
 *  Created on: May 27, 2017
 *      Author: jyates
 */

#ifndef PATTERNS_FLYWEIGHT_H_
#define PATTERNS_FLYWEIGHT_H_

#include <memory>

#include "StandardDefines.h"
#include "UniqueID.h"

template<class Intrinsic, class Extrinsic>
class Flyweight {
    template<typename T, typename U>
    friend class FlyweightFactory;

public:
    UniqueID uniqueID();

    const std::unique_ptr<Intrinsic>& intrinsic() const;

    void updateState(Extrinsic extrinsic);

    Flyweight(const Flyweight& right) = delete;

    virtual ~Flyweight() = default;

private:
    template<typename ...Args>
    explicit Flyweight(const UniqueID& uniqueID, Args&& ...args);

    Flyweight& operator =(const Flyweight& right);

    std::unique_ptr<Intrinsic> m_intrinsicState;
    UniqueID m_identifier;
};

template<class Intrinsic, class Extrinsic>
UniqueID Flyweight<Intrinsic, Extrinsic>::uniqueID() {
    return m_identifier;
}

template<class Intrinsic, class Extrinsic>
const std::unique_ptr<Intrinsic>& Flyweight<Intrinsic, Extrinsic>::intrinsic() const {
    return m_intrinsicState;
}

template<class Intrinsic, class Extrinsic>
void Flyweight<Intrinsic, Extrinsic>::updateState(Extrinsic extrinsic) {
    m_intrinsicState->updateState(extrinsic);
}

template<class Intrinsic, class Extrinsic>
template<typename ...Args>
Flyweight<Intrinsic, Extrinsic>::Flyweight(const UniqueID &uniqueID, Args&& ...args) {
    m_identifier = uniqueID;
    m_intrinsicState = std::make_unique<Intrinsic>(args...);
}

template<class Intrinsic, class Extrinsic>
inline Flyweight<Intrinsic, Extrinsic>& Flyweight<Intrinsic, Extrinsic>::operator =(
        const Flyweight& right) {
    if (right != *this) {
        m_identifier = right.m_identifier;
        m_intrinsicState = std::move(right.m_intrinsicState);
    }
    return *this;
}

#endif /* PATTERNS_FLYWEIGHT_H_ */

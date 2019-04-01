/*
 * FlyweightFactory.h
 *
 *  Created on: May 27, 2017
 *      Author: jyates
 */

#ifndef PATTERNS_FLYWEIGHTFACTORY_H_
#define PATTERNS_FLYWEIGHTFACTORY_H_

#include <unordered_map>
#include <memory>
#include <utility>

#include "Flyweight.h"

#include "UniqueID.h"

template<typename Intrinsic, typename Extrinsic>
class FlyweightFactory {
public:
    FlyweightFactory() = default;
    virtual ~FlyweightFactory() final = default;

    template<typename ...Args>
    std::shared_ptr<Flyweight<Intrinsic, Extrinsic>> getInstance(
            const UniqueID& identifier = UniqueID(), Args&& ...args);

private:
    std::unordered_map<UniqueID,std::shared_ptr<
            Flyweight<Intrinsic, Extrinsic>>> m_flyweightMap;
};

template<typename Intrinsic, typename Extrinsic>
template<typename ...Args>
inline std::shared_ptr<Flyweight<Intrinsic, Extrinsic>>
        FlyweightFactory<Intrinsic, Extrinsic>::getInstance(
                const UniqueID& identifier, Args&& ...args) {
    if (m_flyweightMap.find(identifier) == m_flyweightMap.end()) {
        m_flyweightMap[identifier] =
                // Using make_shared _requires_ a public constructor, so it isn't
                // used here. I think it makes more sense to use *new*, as opposed
                // to using some hacky workaround to be able to use it, or even
                // worse, making the constructor public.
                std::shared_ptr<Flyweight<Intrinsic, Extrinsic>>(
                        new Flyweight<Intrinsic, Extrinsic>(identifier, args...));
    }
    return m_flyweightMap[identifier];
}

#endif /* PATTERNS_FLYWEIGHTFACTORY_H_ */

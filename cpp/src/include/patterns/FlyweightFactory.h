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

#include "../Types/UniqueID.h"

template<class FW, typename Intrinsic, typename Extrinsic>
class FlyweightFactory {
    static_assert(std::is_base_of<Flyweight<Intrinsic, Extrinsic>, FW>::value,
            "FW must be a descendant of Flyweight");
public:
    FlyweightFactory();
    ~FlyweightFactory();

    std::shared_ptr<FW> getInstance(const UniqueID& identifier,
                                    std::shared_ptr<FW> fw = std::shared_ptr<FW>());

private:
    std::unordered_map<UniqueID, std::shared_ptr<FW>> m_flyweightMap;
};

template<class FW, typename Intrinsic, typename Extrinsic>
inline FlyweightFactory<FW, Intrinsic, Extrinsic>::FlyweightFactory() {
}

template<class FW, typename Intrinsic, typename Extrinsic>
inline FlyweightFactory<FW, Intrinsic, Extrinsic>::~FlyweightFactory() {
}

template<class FW, typename Intrinsic, typename Extrinsic>
inline std::shared_ptr<FW> FlyweightFactory<FW, Intrinsic, Extrinsic>::getInstance(
        const UniqueID& identifier, std::shared_ptr<FW> fw) {
    typename std::unordered_map<UniqueID, std::shared_ptr<FW>>::iterator it;
    if ((it = m_flyweightMap.find(identifier)) == m_flyweightMap.end()) {
        if (fw == nullptr) {
            fw = std::make_shared<FW>();
        }
        m_flyweightMap[identifier] = fw;
        return fw;
    } else {
        if (fw != nullptr) {
            throw std::runtime_error("Attempt to override existing instance.");
        }
        return it->second;
    }
}

#endif /* PATTERNS_FLYWEIGHTFACTORY_H_ */

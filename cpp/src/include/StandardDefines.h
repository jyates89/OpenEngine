/*
 * StandardDefines.h
 *
 *  Created on: May 27, 2017
 *      Author: jyates
 */

#ifndef TYPES_STANDARDDEFINES_H_
#define TYPES_STANDARDDEFINES_H_

#ifdef PARTIAL_CXX11_SUPPORT
#define nullptr __null
#endif

#include <memory>
#include <functional>

#if __cplusplus <= 201103L
namespace std {
// make_unique is not available until C++14, so use this implementation
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}
#endif

#endif /* TYPES_STANDARDDEFINES_H_ */

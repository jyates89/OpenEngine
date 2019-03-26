/*
 * Enumerator.h
 *
 *  Created on: Jun 17, 2017
 *      Author: jyates
 */

#ifndef TYPES_ENUMERATOR_H_
#define TYPES_ENUMERATOR_H_

#include <stdexcept>

#include <string>

template<typename Enum, Enum current, Enum... values>
class Enumerator {
friend class Test_Enumerator;
public:
    // The call sizeof is converted to a compile time constant, so we can check the
    //  size of our unpacked values, and add one (to account for 'current').
    static const unsigned long long count = sizeof...(values) + 1;

    // The operation advance() moves the current 'head' templated value
    //  up by one for each recursive call. When a match is found, we assign
    //  the passed in enum to the enum immediately after the 'head'. This is
    //  done at compile time, rather than at run time, so performance should
    //  be optimal.
    static void advance(Enum& value);

    // The operation reverse() works in the same way that advanceEnum does;
    //  each recursive call will move the current 'head' templated value up by one.
    //  When a match is found, we then assign the passed in value to the enum that
    //  comes immediately before itself, rather than after itself, as advance()
    //  does.
    static void reverse(Enum& value);

    // The operation convert() works in the same way that the advance() and
    //  reverse() do. However, every recursive call will increment the converted
    //  value by one, instead of changing the value of the passed in enum. When
    //  compiling with -O2 level optimizations, this matches the performance of a
    //  static_cast, while preserving all type safety.
    static unsigned long long convert(const Enum& value);

private:
    static const std::string INVALID_ENUM_FOR_CONVERSION;
    static const std::string INVALID_ENUM_FOR_ADVANCE;
    static const std::string INVALID_ENUM_FOR_REVERSE;

    template<Enum functionCurrent, Enum functionHead, Enum functionNext, Enum... functionTail>
    static void advanceEnum(Enum& value);

    template<Enum functionCurrent, Enum functionHead>
    static void advanceEnum(Enum& value);

    template<Enum functionCurrent, Enum functionHead, Enum functionNext, Enum... functionTail>
    static void reverseEnum(Enum& value);

    template<Enum functionCurrent, Enum functionHead>
    static void reverseEnum(Enum& value);

    template<Enum functionCurrent, Enum functionHead, Enum functionNext, Enum... functionTail>
    static unsigned long long convertEnum(const Enum& value);

    template<Enum functionCurrent, Enum functionHead>
    static unsigned long long convertEnum(const Enum& value);
};

template<typename Enum, Enum current, Enum... values>
const std::string Enumerator<Enum, current, values...>::INVALID_ENUM_FOR_CONVERSION
    = "unsupported enumeration passed in for conversion operation";

template<typename Enum, Enum current, Enum... values>
const std::string Enumerator<Enum, current, values...>::INVALID_ENUM_FOR_ADVANCE
    = "unsupported enumeration passed in for advance operation";

template<typename Enum, Enum current, Enum... values>
const std::string Enumerator<Enum, current, values...>::INVALID_ENUM_FOR_REVERSE
    = "unsupported enumeration passed in for reverse operation";

template<typename Enum, Enum current, Enum ... values>
inline void Enumerator<Enum, current, values...>::advance(Enum& value) {
    advanceEnum<current, current, values...>(value);
}

template<typename Enum, Enum current, Enum ... values>
template<Enum functionCurrent, Enum functionHead, Enum functionNext, Enum... functionTail>
inline void Enumerator<Enum, current, values...>::advanceEnum(Enum& value) {
    if (value == functionHead) {
        // set the enumeration to the next value in the list
        value = functionNext;
    } else {
        advanceEnum<functionCurrent, functionNext, functionTail...>(value);
    }
}

template<typename Enum, Enum current, Enum ... values>
template<Enum functionCurrent, Enum functionHead>
inline void Enumerator<Enum, current, values...>::advanceEnum(Enum& value) {
    if (value == functionHead) {
        // Getting here means we are at the end of the enumerated list
        //  so we set the value to the beginning again.
        value = functionCurrent;
    } else if (value != functionCurrent) {
        throw std::runtime_error(INVALID_ENUM_FOR_ADVANCE);
    }
}

template<typename Enum, Enum current, Enum ... values>
inline void Enumerator<Enum, current, values...>::reverse(Enum& value) {
    reverseEnum<current, current, values...>(value);
}

template<typename Enum, Enum current, Enum ... values>
template<Enum functionCurrent, Enum functionHead, Enum functionNext, Enum... functionTail>
inline void Enumerator<Enum, current, values...>::reverseEnum(Enum& value) {
    if (value == functionNext) {
        // set the enumeration to the previous value in the list
        value = functionHead;
    } else {
        reverseEnum<functionCurrent, functionNext, functionTail...>(value);
    }
}

template<typename Enum, Enum current, Enum ... values>
template<Enum functionCurrent, Enum functionHead>
inline void Enumerator<Enum, current, values...>::reverseEnum(Enum& value) {
    if (value == functionCurrent) {
        // Getting here means we are the beginning of the enumerated list
        //  so since we are in reverse, set the current value to the last
        //  item in the list.
        value = functionHead;
    } else if (value != functionHead) {
        throw std::runtime_error(INVALID_ENUM_FOR_REVERSE);
    }
}

template<typename Enum, Enum current, Enum ... values>
inline unsigned long long Enumerator<Enum, current, values...>::convert(const Enum& value) {
    if (value == current) {
        return 0;
    }
    return convertEnum<current, current, values...>(value);
}

template<typename Enum, Enum current, Enum ... values>
template<Enum functionCurrent, Enum functionHead, Enum functionNext, Enum ... functionTail>
inline unsigned long long Enumerator<Enum, current, values...>::convertEnum(const Enum& value) {
    if (value != functionHead) {
        return 1 + convertEnum<functionCurrent, functionNext, functionTail...>(value);
    }
    return 0;
}

template<typename Enum, Enum current, Enum ... values>
template<Enum functionCurrent, Enum functionHead>
inline unsigned long long Enumerator<Enum, current, values...>::convertEnum(const Enum& value) {
    if (value == functionCurrent) {
        return 1;
    } else if (value == functionHead) {
        return 0;
    }
    throw std::runtime_error(INVALID_ENUM_FOR_CONVERSION);
}

#endif /* TYPES_ENUMERATOR_H_ */

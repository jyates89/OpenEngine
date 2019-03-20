//
// Created by jyates on 3/16/19.
//

#ifndef OPENENGINE_CONVERSIONS_H
#define OPENENGINE_CONVERSIONS_H
//
// Created by jyates on 8/10/18.
//

#include <stdexcept>

#include <execinfo.h>
#include <dlfcn.h>
#include <cxxabi.h>
#include <sstream>

void print_backtraces();
// Compile-time conversions only!

namespace Avernakis {

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

inline constexpr char to_bin(char character) {
    /*subtract ASCII value for '0' to get real value */
    return static_cast<char>(character - 48);
}

inline constexpr int str_to_integer(const char* str, int accumulatedInput = 0) {
    return *str ? str_to_integer(str + 1, accumulatedInput * 10 + to_bin(*str)) :
           accumulatedInput;
}

inline constexpr char to_ascii(char number) {
    return static_cast<char>(number + 48);
}

constexpr int abs_val(int x) {
    return x < 0 ? -x: x;
}

constexpr int num_digits(int x, int count = 0) {
    return count + x > 0 ?
        1 + num_digits(-x) : x < 10 ?
            1 : 1 + num_digits(x / 10);
}

template<char... args>
struct String {
    const char data[sizeof...(args)] = {args... };
};

template<int size, int x, char... args>
struct NumberBuilder {
    typedef typename NumberBuilder<
            size - 1,
            x / 10,
            '0' + abs_val(x) % 10,
            args...>::type type;
};

template<int x, char... args>
struct NumberBuilder<2, x, args...> {
    typedef String<
            x < 0 ? '-' : '0' + x / 10,
            '0' + abs_val(x) % 10,
            args...> type;
};

template<int x, char... args>
struct NumberBuilder<1, x, args...> {
    typedef String<
            '0' + x,
            args...> type;
};

template<int x>
class NumberString {
private:
    typedef typename NumberBuilder<num_digits(x), x, '\0'>::type type;
    static constexpr type value {};

public:
    static constexpr const char* get() {
        return value.data;
    }
};

template<int x>
constexpr typename NumberString<x>::type NumberString<x>::value;

}


//void print_backtraces() {
//    void* callstack[128] = {};
//    const int maxFrames = sizeof(callstack) / sizeof(callstack[0]);
//    int frames = backtrace(callstack, maxFrames);
//    char** symbols = backtrace_symbols(callstack, frames);
//
//    for (int i = 1; i < frames; i++) {
//        Dl_info info;
//        if (dladdr(callstack[i], &info)) {
//            char* demangled = nullptr;
//            int status;
//            demangled = abi::__cxa_demangle(info.dli_sname, nullptr, 0, &status);
//            printf("%s\n", demangled);
//            free(demangled);
//        } else {
//            printf("%s\n", info.dli_sname);
//        }
//    }
//    free(symbols);
//}

namespace AV = Avernakis;

#endif //OPENENGINE_CONVERSIONS_H

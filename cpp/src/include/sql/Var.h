/*
 * Var.h
 *
 *  Created on: Jul 3, 2017
 *      Author: jyates
 */

#ifndef TYPES_SQL_VAR_H_
#define TYPES_SQL_VAR_H_

#include "../StandardDefines.h"

#include <string>
#include <chrono>
#include <ratio>

#include <cmath>   // std::lround
#include <cstring> // std::strncpy
#include <cstddef> // std::size_t
#include <cstdlib> // std::atoi, std::strtod
#include <cstdio>  // std::snprintf
#include <ctime>   // std::timeval

class Var {
public:
    // Adding new types:
    //  Simply add the type enumeration to the
    //  'VarType' enum class below, and add the
    //  function specialization for set and get.
    enum class VarType {
        UNKNOWN,
        INTEGER,
        LONGLONG,
        STRING,
        CHAR,
        DOUBLE,
        DATETIME,
    };

    Var(VarType constraint = VarType::UNKNOWN);
    ~Var();

    template<typename T>
    void set(T value);

    template<typename T>
    T get();

    std::string constraint() const;

private:
    // Provide the ability to constrain the type,
    //  similar to SQL column constraints. This
    //  is checked via a compile time assertion.
    VarType m_constraint;
    VarType m_lastUsed;
    // The Var will only ever be a single type
    //  at any one time, so save memory by
    //  using a union. We keep track of the
    //  last used type so that we don't clobber
    //  the memory on access (such as if it stores
    //  a memory address to a string; i.e. strVal)
    union {
        int         intVal;
        long long   longVal;
        double      dblVal;
        char        chrVal;
        const char* strVal;
        timeval     timeVal;
    } m_data;
};

inline Var::Var(VarType constraint) :
        m_constraint(constraint),
        m_lastUsed(VarType::UNKNOWN) {
    memset(&m_data, 0, sizeof(m_data));
}

inline Var::~Var() {
    if (m_lastUsed == VarType::STRING) {
        delete[](m_data.strVal);
    }
}

template<>
inline void Var::set<int>(int value) {
    if (m_lastUsed == VarType::STRING) {
        delete[](m_data.strVal);
    }
    m_data.intVal = value;
    m_lastUsed = VarType::INTEGER;
}

template<>
inline int Var::get<int>() {
    switch(m_lastUsed) {
    case VarType::INTEGER:
        return m_data.intVal;
    case VarType::STRING:
        return std::atoi(m_data.strVal);
    case VarType::CHAR:
        return m_data.chrVal;
    case VarType::DOUBLE:
        return std::lround(m_data.dblVal);
    default:
        return 0;
    }
}

template<>
inline void Var::set<long long>(long long value) {
    if (m_lastUsed == VarType::STRING) {
        delete[](m_data.strVal);
    }
    m_data.longVal = value;
    m_lastUsed = VarType::LONGLONG;
}

template<>
inline long long Var::get<long long>() {
    switch(m_lastUsed) {
    case VarType::INTEGER:
        return m_data.intVal;
    case VarType::LONGLONG:
        return m_data.longVal;
    case VarType::STRING:
        return std::atoi(m_data.strVal);
    case VarType::CHAR:
        return m_data.chrVal;
    case VarType::DOUBLE:
        return std::lround(m_data.dblVal);
    case VarType::DATETIME:
        return m_data.timeVal.tv_sec;
    default:
        return 0;
    }
}

template<>
inline void Var::set<double>(double value) {
    if (m_lastUsed == VarType::STRING) {
        delete[](m_data.strVal);
    }
    m_data.dblVal = value;
    m_lastUsed = VarType::DOUBLE;
}

template<>
inline double Var::get<double>() {
    switch(m_lastUsed) {
    case VarType::INTEGER:
        return static_cast<double>(m_data.intVal);
    case VarType::LONGLONG:
        return static_cast<double>(m_data.longVal);
    case VarType::STRING:
        return std::strtod(m_data.strVal, nullptr);
    case VarType::CHAR:
        return static_cast<double>(m_data.chrVal);
    case VarType::DOUBLE:
        return m_data.dblVal;
    case VarType::DATETIME:
        return static_cast<double>(m_data.timeVal.tv_sec) +
                (static_cast<double>(m_data.timeVal.tv_usec) / 1000000);
    default:
        return static_cast<double>(0);
    }
}

template<>
inline void Var::set<char>(char value) {
    if (m_lastUsed == VarType::STRING) {
        delete[](m_data.strVal);
    }
    m_data.chrVal = value;
    m_lastUsed = VarType::CHAR;
}

template<>
inline char Var::get<char>() {
    switch(m_lastUsed) {
    case VarType::INTEGER:
        return static_cast<char>(m_data.intVal);
    case VarType::LONGLONG:
        return static_cast<char>(m_data.longVal);
    case VarType::STRING:
        return m_data.strVal[0];
    case VarType::CHAR:
        return m_data.chrVal;
    case VarType::DOUBLE:
        return static_cast<char>(m_data.dblVal);
    default:
        return 0;
    }
}

template<>
inline void Var::set<std::string>(std::string value) {
    if (m_lastUsed == VarType::STRING) {
        delete[](m_data.strVal);
    }
    std::size_t strLength = value.length();
    char* str = new char[strLength + 1];
    std::memset(str, 0x00, strLength + 1);
    std::strncpy(str, value.c_str(), strLength);
    m_data.strVal = str;
    m_lastUsed = VarType::STRING;
}

template<>
inline std::string Var::get<std::string>() {
    const int bufferSize = 16;
    switch(m_lastUsed) {
    case VarType::INTEGER: {
        char intBuffer[bufferSize] = { 0 };
        std::snprintf(intBuffer, bufferSize, "%d", m_data.intVal);
        return intBuffer;
    }
    case VarType::LONGLONG: {
        char longBuffer[bufferSize] = { 0 };
        std::snprintf(longBuffer, bufferSize, "%l", m_data.longVal);
        return longBuffer;
    }
    case VarType::STRING:
        return m_data.strVal;
    case VarType::CHAR:
        return std::string(1, m_data.chrVal);
    case VarType::DOUBLE: {
        char dblBuffer[bufferSize] = { 0 };
        std::snprintf(dblBuffer, bufferSize, "%f", m_data.dblVal);
        return dblBuffer;
    }
    case VarType::DATETIME: {
        char timeBuffer[bufferSize] = { 0 };
        std::strftime(timeBuffer, bufferSize, "%d", nullptr);
        return timeBuffer;
    }
    default:
        return "";
    }
}

template<>
inline void Var::set<timeval>(timeval value) {
    if (m_lastUsed == VarType::STRING) {
        delete[](m_data.strVal);
    }
}

template<>
inline timeval Var::get<timeval>() {
    const int bufferSize = 16;
    switch(m_lastUsed) {
    case VarType::INTEGER:
    case VarType::LONGLONG:
    case VarType::STRING:
    case VarType::CHAR:
    case VarType::DOUBLE:
    case VarType::DATETIME:
    default:
        return timeval();
    }
}

inline std::string Var::constraint() const {
    switch (m_constraint) {
    case VarType::INTEGER:
        return "INTEGER";
    case VarType::LONGLONG:
        return "BIGINT";
    case VarType::STRING:
    case VarType::CHAR:
        return "TEXT";
    case VarType::DOUBLE:
        return "REAL";
    case VarType::DATETIME:
        return "NUMERIC";
    default:
        return "NONE";
    }
}

#endif /* TYPES_SQL_VAR_H_ */

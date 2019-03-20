//
// Created by jyates on 8/12/18.
//

#ifndef OPENENGINE_LOGGING_H
#define OPENENGINE_LOGGING_H

#include <stdarg.h>
#include <syslog.h>

#include <sys/time.h>
#include <time.h>

#include <string>
#include <type_traits>

#include <cstdio>

#include "Conversions.h"


template<typename T>
std::string to_string(T type) {
    return type.toString();
}

template<>
std::string to_string<const char*>(const char* msg);

class Logging {
public:
    enum class Destination {
        TERMINAL_OUT,
        LOG_FILE_OUT,
        SYSTEM_LOG,
    };

    enum class DetailLevel {
        BASE_LEVEL,
        ERROR_LEVEL,
        WARN_LEVEL,
        INFO_LEVEL,
        DEBUG_LEVEL,
        TRACE_LEVEL,
    };

    explicit Logging(Destination destination = Destination::TERMINAL_OUT,
           std::string logName = "");
    ~Logging();

    void setLogDetail(DetailLevel detailLevel);

    template<typename Arg, typename... Args>
    void print(DetailLevel level, const std::string& file,
               const std::string& function, int line,
               std::string message, Arg current, Args... vars);

    template<typename Arg>
    void print(DetailLevel level, const std::string& file,
               const std::string& function, int line,
               std::string message, Arg current);

    void print(DetailLevel level, const std::string& file,
               const std::string& function, int line,
               std::string message);

    std::string convertDetailLevel(Logging::DetailLevel level) const;

private:
    FILE* m_destinationDescriptor;
    Destination m_logDestination;
    DetailLevel m_logDetailLevel;
};


template<typename Arg, typename... Args>
void Logging::print(DetailLevel level, const std::string& file,
                   const std::string& function, int line,
                   std::string message, Arg current, Args... vars) {
    if (level > m_logDetailLevel) return;
    std::size_t pos = message.find_first_of("{}"), size = 2;
    if (pos != std::string::npos) {
        using namespace std;
        message.replace(pos, size, to_string(current));
    }
    print(level, file, function, line, message, vars...);
}

template<typename Arg>
void Logging::print(DetailLevel level, const std::string& file,
                   const std::string& function, int line,
                   std::string message, Arg current) {
    if (level > m_logDetailLevel) return;
    std::size_t pos = message.find_first_of("{}"), size = 2;
    if (pos != std::string::npos) {
        using namespace std;
        message.replace(pos, size, to_string(current));
    }
    print(level, file, function, line, message);
}

#define AV_LOG_ERROR(instance, ...) {\
    instance.print(Logging::DetailLevel::ERROR_LEVEL, __FILE__,\
    __FUNCTION__, __LINE__, __VA_ARGS__); }

#define AV_LOG_WARN(instance, ...) {\
    instance.print(Logging::DetailLevel::WARN_LEVEL, __FILE__,\
    __FUNCTION__, __LINE__, __VA_ARGS__); }

#define AV_LOG_INFO(instance, ...) {\
    instance.print(Logging::DetailLevel::INFO_LEVEL, __FILE__,\
    __FUNCTION__, __LINE__, __VA_ARGS__); }

#define AV_LOG_DEBUG(instance, ...) {\
    instance.print(Logging::DetailLevel::DEBUG_LEVEL, __FILE__,\
    __FUNCTION__, __LINE__, __VA_ARGS__); }

#define AV_LOG_TRACE(instance, ...) {\
    instance.print(Logging::DetailLevel::TRACE_LEVEL, __FILE__,\
    __FUNCTION__, __LINE__, __VA_ARGS__); }

#endif //OPENENGINE_LOGGING_H

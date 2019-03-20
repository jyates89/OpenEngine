//
// Created by jyates on 8/14/18.
//

#include "Logging.h"

template<>
std::string to_string<const char*>(const char* msg) {
    if (msg == nullptr) return "NULL";
    return msg;
}

Logging::Logging(Logging::Destination destination,
               std::string logName) :
        m_destinationDescriptor(nullptr),
        m_logDestination(destination),
        m_logDetailLevel(Logging::DetailLevel::ERROR_LEVEL) {
    switch(m_logDestination) {
        case Destination::TERMINAL_OUT:
            m_destinationDescriptor = stdout;
            break;
        case Destination::LOG_FILE_OUT:
            m_destinationDescriptor = fopen(logName.c_str(), "a");
            if (m_destinationDescriptor == nullptr) {
                throw std::runtime_error("failed to open log for output");
            }
            break;
        case Destination::SYSTEM_LOG:
            openlog(nullptr, LOG_PID, LOG_USER);
            break;
        default:
            throw std::runtime_error("invalid log destination");
    }
}

Logging::~Logging() {
    switch(m_logDestination) {
        case Destination::TERMINAL_OUT:
            // Nothing special needed for terminal.
            break;
        case Destination::LOG_FILE_OUT:
            std::fflush(m_destinationDescriptor);
            std::fclose(m_destinationDescriptor);
            break;
        case Destination::SYSTEM_LOG:
            closelog();
            break;
    }
}

void Logging::setLogDetail(Logging::DetailLevel detailLevel) {
    print(DetailLevel::BASE_LEVEL, __FILE__, __FUNCTION__, __LINE__,
          "switching from '{}' to '{}' log detail level.",
          static_cast<int>(m_logDetailLevel),
          static_cast<int>(detailLevel));
    m_logDetailLevel = detailLevel;
}

void Logging::print(DetailLevel level, const std::string& file,
                   const std::string& function, int line,
                   std::string message) {
    if (level > m_logDetailLevel) return;

    const time_t now = time(nullptr);
    struct tm timeData = { 0 };
    if (localtime_r(&now, &timeData) != &timeData) {
        throw std::runtime_error("failed to get localtime");
    }

    char timeBuffer[32] = { 0 };
    strftime(timeBuffer, sizeof(timeBuffer), "(%FT%T%z)", &timeData);

    std::string logMessage = convertDetailLevel(level);
    logMessage += ": " + std::string(timeBuffer);
    logMessage += ": " + file.substr(file.find_last_of('/') + 1);
    logMessage += ": " + function;
    logMessage += ": " + std::to_string(line);
    logMessage += ": " + message;
    if (m_logDestination == Destination::SYSTEM_LOG) {
        syslog(LOG_INFO, "%s\n", logMessage.c_str());
    } else {
        std::fprintf(m_destinationDescriptor,
                     "%s\n", logMessage.c_str());
    }
}

std::string Logging::convertDetailLevel(Logging::DetailLevel level) const {
    switch (level) {
        case DetailLevel::BASE_LEVEL:
            return "(BASE)";
        case DetailLevel::ERROR_LEVEL:
            return "(ERROR)";
        case DetailLevel::WARN_LEVEL:
            return "(WARN)";
        case DetailLevel::INFO_LEVEL:
            return "(INFO)";
        case DetailLevel::DEBUG_LEVEL:
            return "(DEBUG)";
        case DetailLevel::TRACE_LEVEL:
            return "(TRACE)";
        default:
            throw std::runtime_error("invalid detail version set");
    }
}

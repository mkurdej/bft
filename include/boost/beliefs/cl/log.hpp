#include <iostream>

#ifndef LOG_TRACE
#define LOG_TRACE(msg) \
    std::cout << "[TRACE] " << msg << "\n";
#endif

#ifndef LOG_DEBUG
#define LOG_DEBUG(msg) \
    std::cout << "[DEBUG] " << msg << "\n";
#endif

#ifndef LOG_INFO
#define LOG_INFO(msg) \
    std::cout << "[INFO ] " << msg << "\n";
#endif

#ifndef LOG_WARN
#define LOG_WARN(msg) \
    std::cout << "[WARN ] " << msg << "\n";
#endif

#ifndef LOG_ERROR
#define LOG_ERROR(msg) \
    std::cout << "[ERROR] " << msg << "\n";
#endif

#ifndef LOG_FATAL
#define LOG_FATAL(msg) \
    std::cout << "[FATAL] " << msg << "\n";
#endif

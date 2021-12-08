#pragma once

#include "defines.h"
#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

#if HRELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

typedef enum log_level{
    LOG_LEVEL_FATAL = 0,
    LOG_LEVEL_ERROR = 1,
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_INFO = 3,
    LOG_LEVEL_DEBUG = 4,
    LOG_LEVEL_TRACE = 5,
} log_level;

b8 initialize_logging();
void shutdown_logging();

HAPI void log_output(log_level level, const char* message, ...);
//FATAL LOG
#define HFATAL(message, ...) log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);
//ERROR LOG
#ifndef HERROR
#define HERROR(message, ...) log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#endif
//WARNING LOG
#if LOG_WARN_ENABLED == 1
#define HWARN(message, ...) log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#else 
#define HWARN(message, ...)
#endif
// INFO LOG
#if LOG_INFO_ENABLED == 1
#define HINFO(message, ...) log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else 
#define HINFO(message, ...)
#endif
//DEBUG LOG
#if LOG_DEBUG_ENABLED == 1
#define HDEBUG(message, ...) log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else 
#define HDEBUG(message, ...)
#endif
//TRACE LOG
#if LOG_TRACE_ENABLED == 1
#define HTRACE(message, ...) log_output(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else 
#define HTRACE(message, ...)
#endif
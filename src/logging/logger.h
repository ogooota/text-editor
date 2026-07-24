#pragma once 

/**
 * TODO: Document everything
 */

#define BACKLOGBUFFER_MAXSIZE 8192

typedef enum LogLevel {
    LOG_LEVEL_FATAL = 0,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_TRACE,
} log_level_t;

void log_output(log_level_t level, const char *msg, ...);

#define FATAL(msg, ...) log_output(LOG_LEVEL_FATAL, msg, ##__VA_ARGS__)
#define ERROR(msg, ...) log_output(LOG_LEVEL_ERROR, msg, ##__VA_ARGS__)
#define WARN(msg, ...) log_output(LOG_LEVEL_WARN, msg, ##__VA_ARGS__)
#define INFO(msg, ...) log_output(LOG_LEVEL_INFO, msg, ##__VA_ARGS__)
#define DEBUG(msg, ...) log_output(LOG_LEVEL_DEBUG, msg, ##__VA_ARGS__)
#define TRACE(msg, ...) log_output(LOG_LEVEL_TRACE, msg, ##__VA_ARGS__)
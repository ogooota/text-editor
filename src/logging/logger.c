#include "asserts.h"
#include "logger.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void report_assertion_failure(const char *expr, const char *msg, const char *fname, i32 lines) {
    log_output( LOG_LEVEL_FATAL, "Assertion failure: %s, message: '%s', in file: %s, line: %d\n", 
                expr, msg, fname, lines );
}

void log_output(log_level_t level, const char *msg, ...) {
    const char *level_labels[] = {
      "[FATAL]: ",
      "[ERROR]: ",
      "[WARN]: ",
      "[INFO]: ",
      "[DEBUG]: ",
      "[TRACE]: ",
    };

    /** 
     * This limits the buffer to 8192 bytes 
     * 
     * TODO: Change to heap
     */
    char buffer[BACKLOGBUFFER_MAXSIZE];
    memset(buffer, 0, sizeof(buffer));

    __builtin_va_list arg_ptr;
    va_start(arg_ptr, msg);
    vsnprintf(buffer, sizeof(buffer), msg, arg_ptr);
    va_end(arg_ptr);

    printf("%s%s\n", level_labels[level], buffer);
}
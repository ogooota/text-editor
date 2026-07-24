#pragma once 

#include "../config/defines.h"

/**
 * Comment this line to disable assertions
 */
#define ASSERTIONS_ENABLED 1

/**
 * TODO: Document everything
 */

#ifdef ASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

void report_assertion_failure(const char *expr, const char *msg, const char *fname, i32 lines);

#define ASSERT(expr)                                            \
if (expr) {}                                                    \
else {                                                          \
    report_assertion_failure(#expr, "", __FILE__, __LINE__);     \
    debugBreak();                                               \
}

#define ASSERT_MESSAGE(expr, msg)                               \
if (expr) {}                                                    \
else {                                                          \
    report_assertion_failure(#expr, msg, __FILE__, __LINE__);    \
    debugBreak();                                               \
}

#endif
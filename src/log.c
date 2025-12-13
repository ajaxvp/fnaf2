#include <stdio.h>
#include <stdarg.h>

static int logf(FILE* dest, const char* level, const char* fmt, va_list args)
{
    int v = 0;
    v += fprintf(dest, "%s: ", level);
    v += vfprintf(dest, fmt, args);
    return v;
}

#define LOG_FUNCTION_GENERATOR(dest, level) \
    int level ## f(const char* fmt, ...) \
    {   \
        va_list args; \
        va_start(args, fmt); \
        int v = logf(dest, #level, fmt, args); \
        va_end(args); \
        return v; \
    }

LOG_FUNCTION_GENERATOR(stdout, info)
LOG_FUNCTION_GENERATOR(stdout, debug)
LOG_FUNCTION_GENERATOR(stdout, warn)
LOG_FUNCTION_GENERATOR(stderr, error)

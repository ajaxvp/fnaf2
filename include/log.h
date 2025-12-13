#ifndef FNAF2_LOG_H
#define FNAF2_LOG_H

#define LOG_PROTOTYPE_GENERATOR(level) int level ## f(const char* fmt, ...);

LOG_PROTOTYPE_GENERATOR(info)
LOG_PROTOTYPE_GENERATOR(debug)
LOG_PROTOTYPE_GENERATOR(warn)
LOG_PROTOTYPE_GENERATOR(error)

#endif

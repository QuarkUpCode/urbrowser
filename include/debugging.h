#ifndef DEBUGGING_H
#define DEBUGGING_H

#include <stdio.h>

// !!! non universal macros
#define DEBUGGING_PREFIX printf("\x1b[34m%s\x1b[0m@\x1b[35m%s\x1b[0m : ", __FILE__, __FUNCTION__);

// #define DEBUG(...)
// #define LOG(...)

#ifndef DEBUG
#define DEBUG(...) DEBUGGING_PREFIX printf(__VA_ARGS__);
#endif

#ifndef LOG
#define LOG(...) DEBUGGING_PREFIX printf(__VA_ARGS__);
#endif

#endif

#pragma once

#include <stdlib.h> //min and max - if exist

#define RELEASE(chunk) free(chunk);chunk = NULL

#ifdef _RELEASE
#define FLUSH(stream)
#else
#define FLUSH(stream) fflush(stream)
#endif

#define LOG_ERROR(...) fprintf(stderr, "ERROR: " __VA_ARGS__ ); fprintf(stderr, "\n"); FLUSH( stderr )
#define LOG_INFO(...) fprintf(stderr, "INFO: " __VA_ARGS__ ); fprintf(stdout, "\n"); FLUSH( stderr )

#ifdef _DEBUG
#define LOG_DEBUG(...) fprintf(stderr, "DEBUG: " __VA_ARGS__ ); fprintf(stdout, "\n"); FLUSH( stderr )
#else
#define LOG_DEBUG(...)
#endif

#ifndef max
#define max(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})
#endif

#ifndef min
#define min(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})
#endif

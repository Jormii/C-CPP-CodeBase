#ifndef C_H
#define C_H

#include <stdint.h>

typedef int32_t i32;

#define MAY(EXPR)  // Explicit comment
#define NOTE(EXPR) // Explicit comment

#ifdef NDEBUG
#define MUST(EXPR)           // Assert. Exits if EXPR is false
#define ASSERTZ(EXPR)        // Assert. Returns 0 if EXPR is false
#define ASSERTC(EXPR, ERRNO) // Assert. Returns ERRNO if EXPR is false
#else
#define MUST(EXPR)                                                             \
    if (!(EXPR)) {                                                             \
        must_cb(#EXPR, __FILE__, __LINE__);                                    \
    }

#define ASSERTZ(EXPR)                                                          \
    if (!(EXPR)) {                                                             \
        assertz_cb(#EXPR, __FILE__, __LINE__);                                 \
        return 0;                                                              \
    }

#define ASSERTC(EXPR, ERRNO)                                                   \
    if (!(EXPR)) {                                                             \
        assertc_cb(ERRNO, #EXPR, __FILE__, __LINE__);                          \
        return (ERRNO);                                                        \
    }
#endif

// Called when MUST() macro evaluates EXPR to false
// This callback must take care of exiting the program
extern void must_cb(const char *expr, const char *file, i32 line);

// Called when ASSERTZ() evaluates EXPR to false
extern void assertz_cb(const char *expr, const char *file, i32 line);

// Called when ASSERTC() evaluates EXPR to false
extern void assertc_cb(i32 errno, const char *expr, const char *file, i32 line);

#endif

#pragma once

#include <stddef.h>
#include <stdint.h>

typedef uint8_t u8;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;

#define MAY(EXPR)  // Explicit comment
#define NOTE(EXPR) // Explicit comment

// To indicate if a function was tested
#define TESTED()
#define UNTESTED(EXPR) MUST(0 && #EXPR)

#ifdef NDEBUG
#define MUST(EXPR)    // Assert. Exits if EXPR is false
#define ASSERTZ(EXPR) // Assert. Returns 0 if EXPR is false
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
#endif

// Called when MUST() macro evaluates EXPR to false
// This callback must take care of exiting the program
extern void must_cb(const char *expr, const char *file, i32 line);

// Called when ASSERTZ() evaluates EXPR to false
extern void assertz_cb(const char *expr, const char *file, i32 line);

#define C_ARR_LEN(c_arr)                                                       \
    TESTED()                                                                   \
    (((c_arr) == NULL) ? 0 : sizeof((c_arr)) / sizeof(*(c_arr)))

#define C_ARR_ASSERT(ptr, len)                                                 \
    TESTED()                                                                   \
    ASSERTZ(ptr != NULL);                                                      \
    ASSERTZ(len >= 0);

#define C_ARR_IDX_ASSERT(ptr, len, idx)                                        \
    TESTED();                                                                  \
    C_ARR_ASSERT(ptr, len);                                                    \
    ASSERTZ(idx >= 0);                                                         \
    ASSERTZ(idx < len);

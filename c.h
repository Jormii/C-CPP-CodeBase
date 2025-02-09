#ifndef C_H
#define C_H

#include <stdint.h>

typedef int32_t i32;
typedef int64_t i64;

#define MAY(EXPR)  // Explicit comment
#define NOTE(EXPR) // Explicit comment

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
    (((c_arr) == NULL) ? 0 : sizeof((c_arr)) / sizeof(*(c_arr)))

// Buffers store a pointer and a length
#define BUF(T)                                                                 \
    typedef struct T##Buf {                                                    \
        T *ptr;                                                                \
        const i32 len;                                                         \
    } T##Buf;                                                                  \
                                                                               \
    T *T##Buf_ptr(T##Buf buf, i32 idx) {                                       \
        _BUF_ASSERT(idx, buf.ptr, buf.len)                                     \
        return buf.ptr + idx;                                                  \
    }                                                                          \
                                                                               \
    const T *T##Buf_ptrc(T##Buf buf, i32 idx) {                                \
        _BUF_ASSERT(idx, buf.ptr, buf.len)                                     \
        return buf.ptr + idx;                                                  \
    }

#define BUF_CONST(T)                                                           \
    typedef struct T##BufConst {                                               \
        const T *ptr;                                                          \
        const i32 len;                                                         \
    } T##BufConst;                                                             \
                                                                               \
    const T *T##BufConst_ptrc(T##BufConst buf, i32 idx) {                      \
        _BUF_ASSERT(idx, buf.ptr, buf.len)                                     \
        return buf.ptr + idx;                                                  \
    }

#define BUF_FROM_C_ARR(c_arr) {.ptr = (c_arr), .len = C_ARR_LEN(c_arr)}

#define _BUF_ASSERT(idx, ptr, len)                                             \
    ASSERTZ(ptr != NULL);                                                      \
    ASSERTZ(idx >= 0);                                                         \
    ASSERTZ(idx < len);

#endif

#ifndef C_H
#define C_H

#include <stdint.h>

typedef int32_t i32;
typedef int64_t i64;

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

#define C_ARR_LEN(c_arr)                                                       \
    (((c_arr) == NULL) ? 0 : sizeof((c_arr)) / sizeof(*(c_arr)))

typedef enum BufEC {
    BUF_OK,
    // Variables
    BUF_PTR_IS_NULL,
    // get() & ptr() inputs
    BUF_UNDERFLOW,
    BUF_OVERFLOW,
    BUF_OUT_PTR_IS_NULL,
} BufEC;

// Buffers store a pointer and a length
#define BUF_DECL(T)                                                            \
    typedef struct T##Buf {                                                    \
        T *ptr;                                                                \
        const i32 len;                                                         \
    } T##Buf;                                                                  \
                                                                               \
    BufEC T##Buf##_get(T##Buf buf, i32 idx, T *out);                           \
    BufEC T##Buf##_ptr(T##Buf buf, i32 idx, T **out);                          \
    BufEC T##Buf##_ptrc(T##Buf buf, i32 idx, const T **out);

#define BUF_CONST_DECL(T)                                                      \
    typedef struct T##BufConst {                                               \
        const T *ptr;                                                          \
        const i32 len;                                                         \
    } T##BufConst;                                                             \
                                                                               \
    BufEC T##BufConst##_get(T##BufConst buf, i32 idx, T *out);                 \
    BufEC T##BufConst##_ptrc(T##BufConst buf, i32 idx, const T **out);

#define BUF_FROM_C_ARR(c_arr) {.ptr = (c_arr), .len = C_ARR_LEN(c_arr)}

#define BUF_IMPL(T)                                                            \
    BufEC T##Buf_get(T##Buf buf, i32 idx, T *out) {                            \
        _BUF_ASSERT_GET(idx, buf.ptr, buf.len, out)                            \
                                                                               \
        *out = buf.ptr[idx];                                                   \
        return BUF_OK;                                                         \
    }                                                                          \
                                                                               \
    BufEC T##Buf_ptr(T##Buf buf, i32 idx, T **out) {                           \
        _BUF_ASSERT_GET(idx, buf.ptr, buf.len, out)                            \
                                                                               \
        *out = buf.ptr + idx;                                                  \
        return BUF_OK;                                                         \
    }                                                                          \
                                                                               \
    BufEC T##Buf_ptrc(T##Buf buf, i32 idx, const T **out) {                    \
        _BUF_ASSERT_GET(idx, buf.ptr, buf.len, out)                            \
                                                                               \
        *out = buf.ptr + idx;                                                  \
        return BUF_OK;                                                         \
    }

#define BUF_CONST_IMPL(T)                                                      \
    BufEC T##BufConst_get(T##BufConst buf, i32 idx, T *out) {                  \
        _BUF_ASSERT_GET(idx, buf.ptr, buf.len, out)                            \
                                                                               \
        *out = buf.ptr[idx];                                                   \
        return BUF_OK;                                                         \
    }                                                                          \
                                                                               \
    BufEC T##BufConst_ptrc(T##BufConst buf, i32 idx, const T **out) {          \
        _BUF_ASSERT_GET(idx, buf.ptr, buf.len, out)                            \
                                                                               \
        *out = buf.ptr + idx;                                                  \
        return BUF_OK;                                                         \
    }

#define _BUF_ASSERT_GET(idx, ptr, len, out)                                    \
    ASSERTC(ptr != NULL, BUF_PTR_IS_NULL);                                     \
    ASSERTC(idx >= 0, BUF_UNDERFLOW);                                          \
    ASSERTC(idx < len, BUF_OVERFLOW);                                          \
    ASSERTC(out != NULL, BUF_OUT_PTR_IS_NULL);

#endif

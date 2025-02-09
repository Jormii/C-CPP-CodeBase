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

// Results wrap a flag and a value
#define RES(T)                                                                 \
    typedef struct T##Res {                                                    \
        i32 ok;                                                                \
        T value;                                                               \
    } T##Res;                                                                  \
                                                                               \
    T *T##Res_get(T##Res *res) {                                               \
        ASSERTZ(res->ok);                                                      \
        return &(res->value);                                                  \
    }                                                                          \
                                                                               \
    const T *T##Res_getc(T##Res *res) {                                        \
        ASSERTZ(res->ok);                                                      \
        return &(res->value);                                                  \
    }

#define RES_C(T)                                                               \
    typedef struct T##Res {                                                    \
        i32 ok;                                                                \
        const T value;                                                         \
    } T##ResC;                                                                 \
                                                                               \
    const T *T##ResC_getc(T##ResC *res) {                                      \
        ASSERTZ(res->ok);                                                      \
        return &(res->value);                                                  \
    }

#define RES_OK(RES, val) (RES){.ok = 1, .value = val};
#define RES_FAIL(RES, EXPR)                                                    \
    if (!(EXPR)) {                                                             \
        assertz_cb(#EXPR, __FILE__, __LINE__);                                 \
        return (RES){.ok = 0};                                                 \
    }

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

#define BUF_C(T)                                                               \
    typedef struct T##BufC {                                                   \
        const T *ptr;                                                          \
        const i32 len;                                                         \
    } T##BufC;                                                                 \
                                                                               \
    const T *T##BufC_ptrc(T##BufC buf, i32 idx) {                              \
        _BUF_ASSERT(idx, buf.ptr, buf.len)                                     \
        return buf.ptr + idx;                                                  \
    }

#define BUF_FROM_C_ARR(c_arr) {.ptr = (c_arr), .len = C_ARR_LEN(c_arr)}

#define _BUF_ASSERT(idx, ptr, len)                                             \
    ASSERTZ(ptr != NULL);                                                      \
    ASSERTZ(idx >= 0);                                                         \
    ASSERTZ(idx < len);

#endif

#pragma once

#include <stddef.h>
#include <stdint.h>

typedef uint8_t u8;
typedef int32_t i32;
typedef uint32_t u32;

#pragma region macro

#define NOTE(EXPR)                   // Explicit comment
#define UNTESTED(MSG) MUST(0 && MSG) // To annotate an untested piece of code

#define NODISCARD __attribute__((warn_unused_result))

#ifdef NDEBUG
#define MAY(EXPR) // Explicit comment

#define MUST(EXPR)              // Assert. Exits if EXPR is false
#define ASSERTZ(EXPR)           // Assert. Returns 0 if EXPR is false
#define ASSERTV(EXPR, err_expr) // Assert. Returns err_expr if EXPR is false
#else
#define MAY(EXPR) EXPR

#define MUST(EXPR)                                                             \
    if (!(EXPR)) {                                                             \
        must_cb(#EXPR, __FILE__, __LINE__);                                    \
    }

#define ASSERTZ(EXPR) ASSERTV(EXPR, 0);

#define ASSERTV(EXPR, err_expr)                                                \
    if (!(EXPR)) {                                                             \
        assert_cb(#EXPR, __FILE__, __LINE__);                                  \
        return err_expr;                                                       \
    }

#endif

// Called when MUST() macro evaluates EXPR to false
// This callback must take care of exiting the program
extern void must_cb(const char *expr, const char *file, i32 line);

// Called when ASSERTZ() or ASSERTV() evaluate EXPR to false
extern void assert_cb(const char *expr, const char *file, i32 line);

#define MIN(x, y) ((x) <= (y)) ? (x) : (y)
#define MAX(x, y) ((x) >= (y)) ? (x) : (y)

#define C_ARR_LEN(c_arr)                                                       \
    (((c_arr) == NULL) ? 0 : sizeof((c_arr)) / sizeof(*(c_arr)))

#define MEMBER_OFFSET(STRUCT, MEMBER) ((size_t)(&(((STRUCT *)0)->MEMBER)))

#pragma endregion

#pragma region function

i32 c_arr_check(const void *ptr, i32 len) NODISCARD;
i32 c_arr_idx_check(const void *ptr, i32 len, i32 idx) NODISCARD;

i32 c_arr_2d_idx(i32 cols, i32 row, i32 col);
i32 c_arr_2d_check(const void *ptr, i32 rows, i32 cols);
i32 c_arr_2d_idx_check( //
    const void *ptr, i32 rows, i32 cols, i32 row, i32 col) NODISCARD;

void prof_dump();
void prof_kick(i32 idx);
void prof_stop(i32 idx);
void prof_rename(i32 idx, const char *name);

#pragma endregion

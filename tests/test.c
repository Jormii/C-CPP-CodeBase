#include "c.h"

BUF(i32)
BUF_CONST(i64)

// c.h::C_ARR_LEN
i32 C_ARR_LEN_test(void) {
    const i32 LEN = 3;

    i32 arr[LEN];
    ASSERTZ(C_ARR_LEN(arr) == LEN);

    return 1;
}

i32 C_ARR_LEN_NULL_test(void) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpointer-arith"
#pragma clang diagnostic ignored "-Wsizeof-pointer-div"
    ASSERTZ(C_ARR_LEN(NULL) == 0);
#pragma clang diagnostic pop

    return 1;
}

i32 C_ARR_LEN_arg_ptr_test(void) {
    const i32 LEN = 3;

    i32 arr[LEN];
    i32 *decay = arr;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsizeof-pointer-div"
    ASSERTZ(C_ARR_LEN(decay) != LEN);
#pragma clang diagnostic pop

    return 1;
}

// c.h::BUF
i32 BUF_ptr_test(void) {
    i32 arr[] = {1, 2, 3};
    i32Buf buf = BUF_FROM_C_ARR(arr);

    for (i32 i = 0; i < buf.len; ++i) {
        i32 *p = i32Buf_ptr(buf, i);
        ASSERTZ(p == (arr + i));
    }

    return 1;
}

i32 BUF_ptrc_test(void) {
    i32 arr[] = {1, 2, 3};
    i32Buf buf = BUF_FROM_C_ARR(arr);

    for (i32 i = 0; i < buf.len; ++i) {
        const i32 *p = i32Buf_ptrc(buf, i);
        ASSERTZ(p == (arr + i));
    }

    return 1;
}

// c.h::BUF_CONST
i32 BUF_CONST_ptrc_test(void) {
    i64 arr[] = {1, 2, 3};
    i64BufConst buf = BUF_FROM_C_ARR(arr);

    for (i32 i = 0; i < buf.len; ++i) {
        const i64 *p = i64BufConst_ptrc(buf, i);
        ASSERTZ(p == (arr + i));
    }

    return 1;
}

// c.h::BUF_FROM_C_ARR
i32 BUF_FROM_C_ARR_test(void) {
#define LEN 3

    i32 arr[LEN] = {1, 2, 3};
    i32Buf buf = BUF_FROM_C_ARR(arr);

    ASSERTZ(buf.ptr == arr);
    ASSERTZ(buf.len == LEN);

    return 1;
#undef LEN
}

i32 BUF_FROM_C_ARR_NULL_test(void) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpointer-arith"
#pragma clang diagnostic ignored "-Wsizeof-pointer-div"
    i32Buf buf = BUF_FROM_C_ARR(NULL);
#pragma clang diagnostic pop

    ASSERTZ(buf.ptr == NULL);
    ASSERTZ(buf.len == 0);

    return 1;
}

// c.h::_BUF_ASSERT
i32 _BUF_ASSERT_call(i32Buf buf, i32 idx) {
    _BUF_ASSERT(idx, buf.ptr, buf.len);
    return 1;
}

i32 _BUF_ASSERT_ptr_is_NULL_test(void) {
    i32Buf buf = {.ptr = NULL, .len = 0};

    i32 ok = _BUF_ASSERT_call(buf, 0);
    ASSERTZ(!ok);

    return 1;
}

i32 _BUF_ASSERT_undeflow_test(void) {
    i32 arr[] = {1, 2, 3};
    i32Buf buf = BUF_FROM_C_ARR(arr);

    i32 ok = _BUF_ASSERT_call(buf, -1);
    ASSERTZ(!ok);

    return 1;
}

i32 _BUF_ASSERT_overflow_test(void) {
    i32 arr[] = {1, 2, 3};
    i32Buf buf = BUF_FROM_C_ARR(arr);

    i32 ok = _BUF_ASSERT_call(buf, buf.len);
    ASSERTZ(!ok);

    return 1;
}

#include "c.h"

BUF_DECL(i32)
BUF_IMPL(i32)
BUF_CONST_DECL(i64)
BUF_CONST_IMPL(i64)

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
i32 BUF_get_test(void) {
    i32 arr[] = {1, 2, 3};
    i32Buf buf = BUF_FROM_C_ARR(arr);

    for (i32 i = 0; i < buf.len; ++i) {
        i32 n;
        ASSERTZ(i32Buf_get(buf, i, &n) == BUF_OK);
        ASSERTZ(n == arr[i]);
    }

    return 1;
}

i32 BUF_get_ptr_is_NULL_test(void) {
    i32Buf buf = {.ptr = NULL, .len = 0};

    i32 n;
    ASSERTZ(i32Buf_get(buf, 0, &n) == BUF_PTR_IS_NULL);

    return 1;
}

i32 BUF_get_undeflow_test(void) {
    i32 arr[] = {1, 2, 3};
    i32Buf buf = BUF_FROM_C_ARR(arr);

    i32 n;
    ASSERTZ(i32Buf_get(buf, -1, &n) == BUF_UNDERFLOW);

    return 1;
}

i32 BUF_get_overflow_test(void) {
    i32 arr[] = {1, 2, 3};
    i32Buf buf = BUF_FROM_C_ARR(arr);

    i32 n;
    ASSERTZ(i32Buf_get(buf, buf.len, &n) == BUF_OVERFLOW);

    return 1;
}

i32 BUF_get_out_ptr_is_NULL_test(void) {
    i32 arr[] = {1, 2, 3};
    i32Buf buf = BUF_FROM_C_ARR(arr);
    ASSERTZ(i32Buf_get(buf, 0, NULL) == BUF_OUT_PTR_IS_NULL);

    return 1;
}

i32 BUF_ptr_test(void) {
    i32 arr[] = {1, 2, 3};
    i32Buf buf = BUF_FROM_C_ARR(arr);

    for (i32 i = 0; i < buf.len; ++i) {
        i32 *p;
        ASSERTZ(i32Buf_ptr(buf, i, &p) == BUF_OK);
        ASSERTZ(p == (arr + i));
    }

    return 1;
}

i32 BUF_ptr_ptr_is_NULL_test(void) {
    i32Buf buf = {.ptr = NULL, .len = 0};

    i32 *p;
    ASSERTZ(i32Buf_ptr(buf, 0, &p) == BUF_PTR_IS_NULL);

    return 1;
}

i32 BUF_ptr_undeflow_test(void) {
    i32 arr[] = {1, 2, 3};
    i32Buf buf = BUF_FROM_C_ARR(arr);

    i32 *p;
    ASSERTZ(i32Buf_ptr(buf, -1, &p) == BUF_UNDERFLOW);

    return 1;
}

i32 BUF_ptr_overflow_test(void) {
    i32 arr[] = {1, 2, 3};
    i32Buf buf = BUF_FROM_C_ARR(arr);

    i32 *p;
    ASSERTZ(i32Buf_ptr(buf, buf.len, &p) == BUF_OVERFLOW);

    return 1;
}

i32 BUF_ptr_out_ptr_is_NULL_test(void) {
    i32 arr[] = {1, 2, 3};
    i32Buf buf = BUF_FROM_C_ARR(arr);
    ASSERTZ(i32Buf_ptr(buf, 0, NULL) == BUF_OUT_PTR_IS_NULL);

    return 1;
}

i32 BUF_ptr_const_test(void) {
    i32 arr[] = {1, 2, 3};
    i32Buf buf = BUF_FROM_C_ARR(arr);

    for (i32 i = 0; i < buf.len; ++i) {
        const i32 *p;
        ASSERTZ(i32Buf_ptr_const(buf, i, &p) == BUF_OK);
        ASSERTZ(p == (arr + i));
    }

    return 1;
}

i32 BUF_ptr_const_ptr_is_NULL_test(void) {
    i32Buf buf = {.ptr = NULL, .len = 0};

    const i32 *p;
    ASSERTZ(i32Buf_ptr_const(buf, 0, &p) == BUF_PTR_IS_NULL);

    return 1;
}

i32 BUF_ptr_const_undeflow_test(void) {
    i32 arr[] = {1, 2, 3};
    i32Buf buf = BUF_FROM_C_ARR(arr);

    const i32 *p;
    ASSERTZ(i32Buf_ptr_const(buf, -1, &p) == BUF_UNDERFLOW);

    return 1;
}

i32 BUF_ptr_const_overflow_test(void) {
    i32 arr[] = {1, 2, 3};
    i32Buf buf = BUF_FROM_C_ARR(arr);

    const i32 *p;
    ASSERTZ(i32Buf_ptr_const(buf, buf.len, &p) == BUF_OVERFLOW);

    return 1;
}

i32 BUF_ptr_const_out_ptr_is_NULL_test(void) {
    i32 arr[] = {1, 2, 3};
    i32Buf buf = BUF_FROM_C_ARR(arr);
    ASSERTZ(i32Buf_ptr_const(buf, 0, NULL) == BUF_OUT_PTR_IS_NULL);

    return 1;
}

// c.h::BUF_CONST
i32 BUF_CONST_get_test(void) {
    i64 arr[] = {1, 2, 3};
    i64BufConst buf = BUF_FROM_C_ARR(arr);

    for (i32 i = 0; i < buf.len; ++i) {
        i64 n;
        ASSERTZ(i64BufConst_get(buf, i, &n) == BUF_OK);
        ASSERTZ(n == arr[i]);
    }

    return 1;
}

i32 BUF_CONST_get_ptr_is_NULL_test(void) {
    i64BufConst buf = {.ptr = NULL, .len = 0};

    i64 n;
    ASSERTZ(i64BufConst_get(buf, 0, &n) == BUF_PTR_IS_NULL);

    return 1;
}

i32 BUF_CONST_get_undeflow_test(void) {
    i64 arr[] = {1, 2, 3};
    i64BufConst buf = BUF_FROM_C_ARR(arr);

    i64 n;
    ASSERTZ(i64BufConst_get(buf, -1, &n) == BUF_UNDERFLOW);

    return 1;
}

i32 BUF_CONST_get_overflow_test(void) {
    i64 arr[] = {1, 2, 3};
    i64BufConst buf = BUF_FROM_C_ARR(arr);

    i64 n;
    ASSERTZ(i64BufConst_get(buf, buf.len, &n) == BUF_OVERFLOW);

    return 1;
}

i32 BUF_CONST_get_out_ptr_is_NULL_test(void) {
    i64 arr[] = {1, 2, 3};
    i64BufConst buf = BUF_FROM_C_ARR(arr);
    ASSERTZ(i64BufConst_get(buf, 0, NULL) == BUF_OUT_PTR_IS_NULL);

    return 1;
}

i32 BUF_CONST_ptr_const_test(void) {
    i64 arr[] = {1, 2, 3};
    i64BufConst buf = BUF_FROM_C_ARR(arr);

    for (i32 i = 0; i < buf.len; ++i) {
        const i64 *p;
        ASSERTZ(i64BufConst_ptr_const(buf, i, &p) == BUF_OK);
        ASSERTZ(p == (arr + i));
    }

    return 1;
}

i32 BUF_CONST_ptr_const_ptr_is_NULL_test(void) {
    i64BufConst buf = {.ptr = NULL, .len = 0};

    const i64 *p;
    ASSERTZ(i64BufConst_ptr_const(buf, 0, &p) == BUF_PTR_IS_NULL);

    return 1;
}

i32 BUF_CONST_ptr_const_undeflow_test(void) {
    i64 arr[] = {1, 2, 3};
    i64BufConst buf = BUF_FROM_C_ARR(arr);

    const i64 *p;
    ASSERTZ(i64BufConst_ptr_const(buf, -1, &p) == BUF_UNDERFLOW);

    return 1;
}

i32 BUF_CONST_ptr_const_overflow_test(void) {
    i64 arr[] = {1, 2, 3};
    i64BufConst buf = BUF_FROM_C_ARR(arr);

    const i64 *p;
    ASSERTZ(i64BufConst_ptr_const(buf, buf.len, &p) == BUF_OVERFLOW);

    return 1;
}

i32 BUF_CONST_ptr_const_out_ptr_is_NULL_test(void) {
    i64 arr[] = {1, 2, 3};
    i64BufConst buf = BUF_FROM_C_ARR(arr);
    ASSERTZ(i64BufConst_ptr_const(buf, 0, NULL) == BUF_OUT_PTR_IS_NULL);

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

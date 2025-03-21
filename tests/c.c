#include "c.h"

// c.h::(Macros)
i32 MIN_test(void) {
    i32 min = MIN(1, 2);
    i32 expected_min = 1;
    ASSERTZ(min == expected_min);

    i32 min_expr = MIN(1 + 2, 2);
    i32 expected_min_expr = 2;
    ASSERTZ(min_expr == expected_min_expr);

    return 1;
}

i32 MAX_test(void) {
    i32 max = MAX(1, 2);
    i32 expected_max = 2;
    ASSERTZ(max == expected_max);

    i32 max_expr = MAX(1 + 2, 2);
    i32 expected_max_expr = 3;
    ASSERTZ(max_expr == expected_max_expr);

    return 1;
}

i32 C_ARR_LEN_test(void) {
    i32 arr[3];
    ASSERTZ(C_ARR_LEN(arr) == 3);

    return 1;
}

i32 C_ARR_LEN_NULL_test(void) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-arith"
#pragma GCC diagnostic ignored "-Wsizeof-pointer-div"
    ASSERTZ(C_ARR_LEN(NULL) == 0);
#pragma GCC diagnostic pop

    return 1;
}

i32 C_ARR_LEN_arg_ptr_test(void) {
    i32 arr[3];
    i32 *decay = arr;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsizeof-pointer-div"
    ASSERTZ(C_ARR_LEN(decay) != 3);
#pragma GCC diagnostic pop

    return 1;
}

// c.h::C_ARR_ASSERT
i32 C_ARR_ASSERT_call(const i32 *ptr, i32 len) {
    C_ARR_ASSERT(ptr, len);
    return 1;
}

i32 C_ARR_ASSERT_ptr_is_NULL_test(void) {
    i32 *ptr = NULL;
    i32 len = 0;

    i32 ok = C_ARR_ASSERT_call(ptr, len);
    ASSERTZ(!ok);

    return 1;
}

i32 C_ARR_ASSERT_len_is_negative_test(void) {
    i32 arr[] = {1, 2, 3};
    i32 len = -1;

    i32 ok = C_ARR_ASSERT_call(arr, len);
    ASSERTZ(!ok);

    return 1;
}

// c.h::C_ARR_IDX_ASSERT
i32 C_ARR_IDX_ASSERT_call(const i32 *ptr, i32 len, i32 idx) {
    C_ARR_IDX_ASSERT(ptr, len, idx);
    return 1;
}

i32 C_ARR_IDX_ASSERT_underflow_test(void) {
    i32 arr[] = {1, 2, 3};
    i32 len = C_ARR_LEN(arr);
    i32 idx = -1;

    i32 ok = C_ARR_IDX_ASSERT_call(arr, len, idx);
    ASSERTZ(!ok);

    return 1;
}

i32 C_ARR_IDX_ASSERT_overflow_test(void) {
    i32 arr[] = {1, 2, 3};
    i32 len = C_ARR_LEN(arr);
    i32 idx = len + 1;

    i32 ok = C_ARR_IDX_ASSERT_call(arr, len, idx);
    ASSERTZ(!ok);

    return 1;
}

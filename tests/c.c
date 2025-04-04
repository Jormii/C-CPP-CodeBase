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

typedef struct __Struct_st {
    u8 byte;
    int64_t integer;
} __Struct;

i32 MEMBER_OFFSET_test(void) {
    ASSERTZ(MEMBER_OFFSET(__Struct, byte) == 0);
    ASSERTZ(MEMBER_OFFSET(__Struct, integer) != sizeof(u8));
    ASSERTZ(MEMBER_OFFSET(__Struct, integer) == sizeof(int64_t));

    return 1;
}

// c.h::(Functions)
i32 c_arr_check_test(void) {
    i32 val = 0;
    ASSERTZ(c_arr_check(NULL, 0) == 0);
    ASSERTZ(c_arr_check(&val, -1) == 0);

    return 1;
}

i32 c_arr_idx_check_test(void) {
    i32 val = 0;
    i32 len = 1;
    ASSERTZ(c_arr_idx_check(NULL, len, 0) == 0);
    ASSERTZ(c_arr_idx_check(&val, len, -1) == 0);
    ASSERTZ(c_arr_idx_check(&val, len, len + 1) == 0);

    return 1;
}

i32 c_arr_2d_idx_test(void) {
    i32 cols = 3;
    ASSERTZ(c_arr_2d_idx(cols, 0, 0) == 0);
    ASSERTZ(c_arr_2d_idx(cols, 2, 0) == 6);
    ASSERTZ(c_arr_2d_idx(cols, 0, 2) == 2);
    ASSERTZ(c_arr_2d_idx(cols, 2, 2) == 8);

    return 1;
}

i32 c_arr_2d_idx_check_test(void) {
    i32 val = 0;
    i32 rows = 1;
    i32 cols = 1;
    ASSERTZ(c_arr_2d_idx_check(NULL, rows, cols, 0, 0) == 0);
    ASSERTZ(c_arr_2d_idx_check(&val, rows, cols, -1, 0) == 0);
    ASSERTZ(c_arr_2d_idx_check(&val, rows, cols, 0, -1) == 0);
    ASSERTZ(c_arr_2d_idx_check(&val, rows, cols, -1, -1) == 0);
    ASSERTZ(c_arr_2d_idx_check(&val, rows, cols, rows, 0) == 0);
    ASSERTZ(c_arr_2d_idx_check(&val, rows, cols, 0, cols) == 0);
    ASSERTZ(c_arr_2d_idx_check(&val, rows, cols, rows, cols) == 0);

    return 1;
}

#include "cpp.hpp"

// cpp.hpp::SWAP
i32 SWAP_test(void) {
    i32 one = 1;
    i32 two = 2;
    SWAP(one, two);

    ASSERTZ(one == 2);
    ASSERTZ(two == 1);

    return 1;
}

// cpp.hpp::Buf
i32 Buf_get_test(void) {
    i32 arr[] = {1, 2, 3};

    Buf<i32> buf = BUF_FROM_C_ARR(arr);
    const Buf<i32> buf_const = BUF_FROM_C_ARR(arr);

    for (i32 i = 0; i < buf.len; ++i) {
        i32 *p = buf.get(i);
        const i32 *pc = buf.get(i);
        const i32 *pc_const = buf_const.get(i);

        ASSERTZ(p == (arr + i));
        ASSERTZ(pc == (arr + i));
        ASSERTZ(pc_const == (arr + i));
    }

    return 1;
}

// cpp.hpp::Arr
i32 Arr_get_test(void) {
    Arr<3, i32> arr = {1, 2, 3};
    const Arr<3, i32> arr_const = {1, 2, 3};
    ASSERTZ(C_ARR_LEN(arr.ptr) == C_ARR_LEN(arr_const.ptr));

    i32 len = C_ARR_LEN(arr.ptr);
    for (i32 i = 0; i < len; ++i) {
        i32 *p = arr.get(i);
        const i32 *pc = arr.get(i);
        const i32 *pc_const = arr_const.get(i);

        ASSERTZ(p == (arr.ptr + i));
        ASSERTZ(pc == (arr.ptr + i));
        ASSERTZ(pc_const == (arr_const.ptr + i));
    }

    return 1;
}

i32 Arr_mag_test(void) {
    V2i u = {3, 4};
    float expected_mag = 5.0f;

    float mag = u.mag();
    ASSERTZ(eq(mag, expected_mag));

    return 1;
}

i32 Arr_norm_test(void) {
    V2i u = {3, 4};
    float expected_mag = 5.0f;
    Arr<2, float> expected_norm = {3.0f / expected_mag, 4.0f / expected_mag};

    Arr norm = u.norm();
    ASSERTZ(norm == expected_norm);

    return 1;
}

i32 Arr_dot_test(void) {
    V2i u = {2, 3};
    V2i v = {4, 5};
    float expected_dot = (2 * 4) + (3 * 5);

    i32 dot = V2i::dot(u, v);
    ASSERTZ(dot == expected_dot);

    return 1;
}

i32 Arr_cross_test(void) {
    V3i u = {2, 3, 4};
    V3i v = {5, 6, 7};
    V3i expected_cross = {-3, 6, -3};

    V3i cross = V3i::cross(u, v);
    ASSERTZ(cross == expected_cross);

    return 1;
}

i32 Arr_bary_test(void) {
    V2i u = {3, 2};
    V2i v = {5, 3};
    V2i w = {2, 4};
    float a = 0.4f;
    float b = 0.2f;
    float g = 0.4f;
    V2f expected_bary = {3, 3};

    V2f bary = V2i::bary(u, v, w, a, b, g);
    ASSERTZ(bary == expected_bary);

    return 1;
}

i32 Arr_operator_sub_test(void) {
    V2i u = {2, 3};
    V2i v = {4, 9};
    V2i expected_sub = {-2, -6};

    V2i sub = u - v;
    ASSERTZ(sub == expected_sub);

    return 1;
}

i32 Arr_operator_eq_test(void) {
    V2i u = {2, 3};
    V2i v = {2, 9};
    V2i w = {9, 3};

    ASSERTZ(u == u);
    ASSERTZ(u != v);
    ASSERTZ(u != w);
    ASSERTZ(v != w);

    return 1;
}

// cpp.hpp::(Functions)
i32 eq_test(void) {
    ASSERTZ(eq(2, 2));
    ASSERTZ(!eq(2, 3));

    return 1;
}

i32 eq__float_test(void) {
    ASSERTZ(eq(2.0f, 2.0f));
    ASSERTZ(eq(2.0f, 2.0f + __FLT_EPSILON__));
    ASSERTZ(!eq(2.0f, 2.0f + 2 * __FLT_EPSILON__));

    return 1;
}

i32 mag_v_test(void) {
    i32 u[] = {3, 4};
    float expected_mag = 5.0f;

    float mag = mag_v(u, C_ARR_LEN(u));
    ASSERTZ(eq(mag, expected_mag));

    return 1;
}

i32 norm_v_test(void) {
    i32 u[] = {3, 4};
    float mag = mag_v(u, C_ARR_LEN(u));
    float expected_norm[C_ARR_LEN(u)] = {3.0f / mag, 4.0f / mag};

    float norm[C_ARR_LEN(u)];
    float *out = norm_v(u, norm, C_ARR_LEN(u));
    ASSERTZ(out != NULL);
    ASSERTZ(eq_v(norm, expected_norm, C_ARR_LEN(u)));

    return 1;
}

i32 dot_v_test(void) {
    i32 u[] = {2, 3};
    i32 v[C_ARR_LEN(u)] = {4, 5};
    i32 expected_dot = (2 * 4) + (3 * 5);

    i32 dot = dot_v(u, v, C_ARR_LEN(u));
    ASSERTZ(dot == expected_dot);

    return 1;
}

i32 eq_v_test(void) {
    i32 u[] = {2, 3};
    i32 v[C_ARR_LEN(u)] = {2, 9};
    i32 w[C_ARR_LEN(u)] = {9, 3};

    ASSERTZ(eq_v(u, u, C_ARR_LEN(u)));
    ASSERTZ(!eq_v(u, v, C_ARR_LEN(u)));
    ASSERTZ(!eq_v(u, w, C_ARR_LEN(u)));
    ASSERTZ(!eq_v(v, w, C_ARR_LEN(u)));

    return 1;
}

i32 sub_v_test(void) {
    i32 u[] = {2, 3};
    i32 v[C_ARR_LEN(u)] = {4, 9};
    i32 expected_sub[C_ARR_LEN(u)] = {-2, -6};

    i32 sub[C_ARR_LEN(u)];
    i32 *out = sub_v(u, v, sub, C_ARR_LEN(u));
    ASSERTZ(out != NULL);
    ASSERTZ(eq_v(sub, expected_sub, C_ARR_LEN(u)));

    return 1;
}

i32 bary_v_test(void) {
    i32 u[] = {3, 2};
    i32 v[C_ARR_LEN(u)] = {5, 3};
    i32 w[C_ARR_LEN(u)] = {2, 4};
    float a = 0.4f;
    float b = 0.2f;
    float g = 0.4f;
    float expected_bary[C_ARR_LEN(u)] = {3, 3};

    float bary[C_ARR_LEN(u)];
    float *out = bary_v(u, v, w, a, b, g, bary, C_ARR_LEN(u));
    ASSERTZ(out != NULL);
    ASSERTZ(eq_v(bary, expected_bary, C_ARR_LEN(u)));

    return 1;
}

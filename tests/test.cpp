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
i32 Arr_len_test(void) {
    Arr<3, i32> arr;
    ASSERTZ(arr.len() == 3);

    return 1;
}

i32 Arr_get_test(void) {
    Arr<3, i32> arr = {0, 1, 2};
    const Arr<3, i32> arr_const = {0, 1, 2};
    ASSERTZ(arr.len() == arr_const.len());

    i32 len = arr.len();
    for (i32 i = 0; i < len; ++i) {
        i32 *p = arr.get(i);
        const i32 *pc = arr.get(i);
        const i32 *pc_const = arr_const.get(i);

        ASSERTZ(*p == i);
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
    V2f expected_norm = {3.0f / expected_mag, 4.0f / expected_mag};

    Arr norm = u.norm();
    ASSERTZ(norm == expected_norm);

    return 1;
}

i32 Arr_ones_test(void) {
    V2i expected_ones = {1, 1};

    V2i ones = V2i::ones();
    ASSERTZ(ones == expected_ones);

    return 1;
}

i32 Arr_zeros_test(void) {
    V2i expeceted_zeros = {0, 0};

    V2i zeros = V2i::zeros();
    ASSERTZ(zeros == expeceted_zeros);

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

// cpp.hpp::Mat
i32 Mat_len_test(void) {
    Mat<2, i32> mat;
    ASSERTZ(mat.len() == 2);

    return 1;
}

i32 Mat_get_test(void) {
    Mat<2, i32> mat = {
        0, 1, //
        2, 3, //
    };
    const Mat<2, i32> mat_const = {
        0, 1, //
        2, 3, //
    };
    ASSERTZ(mat.len() == mat_const.len());

    i32 len = mat.len();
    for (i32 i = 0, idx = 0; i < len; ++i) {
        for (i32 j = 0; j < len; ++j, ++idx) {
            i32 *p = mat.get(i, j);
            const i32 *pc = mat.get(i, j);
            const i32 *pc_const = mat_const.get(i, j);

            i32 idx = i * len + j;
            ASSERTZ(*p == idx);
            ASSERTZ(p == (mat.ptr + idx));
            ASSERTZ(pc == (mat.ptr + idx));
            ASSERTZ(pc_const == (mat_const.ptr + idx));
        }
    }

    return 1;
}

i32 Mat_trans_test(void) {
    M2i mat = {
        0, 1, //
        2, 3, //
    };
    M2i expected_trans = {
        0, 2, //
        1, 3, //
    };

    M2i trans = mat.trans();
    ASSERTZ(trans == expected_trans);

    return 1;
}

i32 Mat_I_test(void) {
    M2i expected_I = {
        1, 0, //
        0, 1, //
    };

    M2i I = M2i::I();
    ASSERTZ(I == expected_I);

    return 1;
}

i32 Mat_ones_test(void) {
    M2i expected_ones = {
        1, 1, //
        1, 1, //
    };

    M2i ones = M2i::ones();
    ASSERTZ(ones == expected_ones);

    return 1;
}

i32 Mat_zeros_test(void) {
    M2i expected_zeros = {
        0, 0, //
        0, 0, //
    };

    M2i zeros = M2i::zeros();
    ASSERTZ(zeros == expected_zeros);

    return 1;
}

i32 Mat_operator_mult_Arr_test(void) {
    M2i m = {
        4, 5, //
        6, 7, //
    };
    V2i u = {2, 3};
    V2i expected_vmult = {23, 33};

    V2i vmult = m * u;
    ASSERTZ(vmult == expected_vmult);

    return 1;
}

i32 Mat_operator_mult_Mat_test(void) {
    M2i m = {
        2, 3, //
        4, 5, //
    };
    M2i n = {
        6, 7, //
        8, 9, //
    };
    M2i expected_mmult = {
        36, 41, //
        64, 73, //
    };

    M2i mmult = m * n;
    ASSERTZ(mmult == expected_mmult);

    return 1;
}

i32 Mat_operator_eq_test(void) {
    M2i m = {
        2, 3, //
        4, 5, //
    };
    M2i n = {
        2, 4, //
        3, 5, //
    };
    M2i o = {
        4, 5, //
        2, 3, //
    };

    ASSERTZ(m == m);
    ASSERTZ(m != n);
    ASSERTZ(m != o);
    ASSERTZ(n != o);

    return 1;
}

// cpp.hpp::(Functions)
i32 min_test(void) {
    i32 a = 1;
    i32 b = 2;
    i32 expected_min = a;

    i32 min_ = min(a, b);
    ASSERTZ(min_ == expected_min);

    return 1;
}

i32 max_test(void) {
    i32 a = 1;
    i32 b = 2;
    i32 expected_max = b;

    i32 max_ = max(a, b);
    ASSERTZ(max_ == expected_max);

    return 1;
}

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

i32 fill_v_test(void) {
    i32 x = 2;
    i32 expected_fill[] = {x, x};

    i32 fill[C_ARR_LEN(expected_fill)];
    const i32 *out = fill_v(x, fill, C_ARR_LEN(expected_fill));
    ASSERTZ(out != NULL);
    ASSERTZ(eq_v(fill, expected_fill, C_ARR_LEN(expected_fill)));

    return 1;
}

i32 norm_v_test(void) {
    i32 u[] = {3, 4};
    float mag = mag_v(u, C_ARR_LEN(u));
    float expected_norm[C_ARR_LEN(u)] = {3.0f / mag, 4.0f / mag};

    float norm[C_ARR_LEN(u)];
    const float *out = norm_v(u, norm, C_ARR_LEN(u));
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
    const i32 *out = sub_v(u, v, sub, C_ARR_LEN(u));
    ASSERTZ(out != NULL);
    ASSERTZ(eq_v(sub, expected_sub, C_ARR_LEN(u)));

    return 1;
}

i32 mix_v_test(void) {
    i32 u[] = {2, 3};
    i32 v[C_ARR_LEN(u)] = {8, 17};
    float t = 0.5f;
    float expected_mix[C_ARR_LEN(u)] = {5, 10};

    float mix[C_ARR_LEN(u)];
    const float *out = mix_v(u, v, t, mix, C_ARR_LEN(u));
    ASSERTZ(out != NULL);
    ASSERTZ(eq_v(mix, expected_mix, C_ARR_LEN(u)));

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
    const float *out = bary_v(u, v, w, a, b, g, bary, C_ARR_LEN(u));
    ASSERTZ(out != NULL);
    ASSERTZ(eq_v(bary, expected_bary, C_ARR_LEN(u)));

    return 1;
}

i32 I_m_test(void) {
    i32 expected_I[] = {
        1, 0, //
        0, 1, //
    };

    i32 I[C_ARR_LEN(expected_I)];
    const i32 *out = I_m(I, C_ARR_LEN(expected_I) >> 1);
    ASSERTZ(out != NULL);
    ASSERTZ(eq_v(I, expected_I, C_ARR_LEN(expected_I)));

    return 1;
}

i32 fill_m_test(void) {
    i32 x = 2;
    i32 expected_fill[] = {
        x, x, //
        x, x, //
    };

    i32 fill[C_ARR_LEN(expected_fill)];
    const i32 *out = fill_m(x, fill, C_ARR_LEN(expected_fill) >> 1);
    ASSERTZ(out != NULL);
    ASSERTZ(eq_v(fill, expected_fill, C_ARR_LEN(expected_fill)));

    return 1;
}

i32 trans_m_test(void) {
    i32 m[] = {
        0, 1, //
        2, 3, //
    };
    i32 expected_trans[C_ARR_LEN(m)] = {
        0, 2, //
        1, 3, //
    };

    i32 trans[C_ARR_LEN(m)];
    const i32 *out = trans_m(m, trans, C_ARR_LEN(m) >> 1);
    ASSERTZ(out != NULL);
    ASSERTZ(eq_v(trans, expected_trans, C_ARR_LEN(m)));

    return 1;
}

i32 vmult_m_test(void) {
    i32 m[] = {
        4, 5, //
        6, 7, //
    };
    i32 u[C_ARR_LEN(m) >> 1] = {2, 3};
    i32 expected_vmult[C_ARR_LEN(u)] = {23, 33};

    i32 vmult[C_ARR_LEN(u)];
    const i32 *out = vmult_m(m, u, vmult, C_ARR_LEN(u));
    ASSERTZ(out != NULL);
    ASSERTZ(eq_v(vmult, expected_vmult, C_ARR_LEN(u)));

    return 1;
}

i32 mmult_m_test(void) {
    i32 m[] = {
        2, 3, //
        4, 5, //
    };
    i32 n[C_ARR_LEN(m)] = {
        6, 7, //
        8, 9, //
    };
    i32 expected_mmult[C_ARR_LEN(m)] = {
        36, 41, //
        64, 73, //
    };

    i32 mmult[C_ARR_LEN(m)];
    const i32 *out = mmult_m(m, n, mmult, C_ARR_LEN(m) >> 1);
    ASSERTZ(out != NULL);
    ASSERTZ(eq_v(mmult, expected_mmult, C_ARR_LEN(m)));

    return 1;
}

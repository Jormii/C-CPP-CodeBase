#include "cpp.hpp"

// cpp.hpp::(Macros)
i32 SWAP_test(void) {
    i32 one = 1;
    i32 two = 2;
    SWAP(one, two);

    ASSERTZ(one == 2);
    ASSERTZ(two == 1);

    return 1;
}

// cpp.hpp::Buf
i32 Buf_end_test(void) {
    i32 arr[] = {1, 2, 3};

    Buf<i32> buf = BUF_FROM_C_ARR(arr);
    const Buf<i32> buf_const = BUF_FROM_C_ARR(arr);

    i32 *end = buf.end();
    const i32 *endc = buf.end();
    const i32 *endc_const = buf_const.end();

    ASSERTZ(end == (arr + C_ARR_LEN(arr)));
    ASSERTZ(endc == (arr + C_ARR_LEN(arr)));
    ASSERTZ(endc_const == (arr + C_ARR_LEN(arr)));

    return 1;
}

i32 Buf_operator_indirect_test(void) {
    i32 arr[] = {1, 2, 3};

    Buf<i32> buf = BUF_FROM_C_ARR(arr);
    const Buf<i32> buf_const = BUF_FROM_C_ARR(arr);

    i32 &p = *buf;
    const i32 &pc = *buf;
    const i32 &pc_const = *buf_const;

    ASSERTZ(p == arr[0]);
    ASSERTZ(pc == arr[0]);
    ASSERTZ(pc_const == arr[0]);

    return 1;
}

i32 Buf_operator_subscript_test(void) {
    i32 arr[] = {1, 2, 3};

    Buf<i32> buf = BUF_FROM_C_ARR(arr);
    const Buf<i32> buf_const = BUF_FROM_C_ARR(arr);

    for (i32 i = 0; i < buf.len; ++i) {
        i32 &p = buf[i];
        const i32 &pc = buf[i];
        const i32 &pc_const = buf_const[i];

        ASSERTZ(p == arr[i]);
        ASSERTZ(pc == arr[i]);
        ASSERTZ(pc_const == arr[i]);
    }

    return 1;
}

i32 Buf_operator_add_test(void) {
    i32 arr[] = {1, 2, 3};

    Buf<i32> buf = BUF_FROM_C_ARR(arr);
    const Buf<i32> buf_const = BUF_FROM_C_ARR(arr);

    for (i32 i = 0; i < buf.len; ++i) {
        i32 *p = buf + i;
        const i32 *pc = buf + i;
        const i32 *pc_const = buf_const + i;

        ASSERTZ(p == arr + i);
        ASSERTZ(pc == arr + i);
        ASSERTZ(pc_const == arr + i);
    }

    return 1;
}

// cpp.hpp::Buf2D
i32 Buf2D_get_test(void) {
    i32 arr[] = {
        2, 3, 4, //
        5, 6, 7, //
    };
    const i32 arr_const[] = {
        2, 3, 4, //
        5, 6, 7, //
    };

    Buf2D buf = {arr, 2, 3};
    Buf2D buf_const = {arr_const, 2, 3};

    for (i32 i = 0; i < buf.rows; ++i) {
        for (i32 j = 0; j < buf.cols; ++j) {
            i32 &p = buf.get(i, j);
            const i32 &pc = buf.get(i, j);
            const i32 &pc_const = buf.get(i, j);

            i32 idx = c_arr_2d_idx(buf.cols, i, j);
            ASSERTZ(p == buf.ptr[idx]);
            ASSERTZ(pc == buf.ptr[idx]);
            ASSERTZ(pc_const == buf_const.ptr[idx]);
        }
    }

    return 1;
}

i32 Buf2D_len_test(void) {
    i32 arr[] = {
        1, 2, 3, //
        4, 5, 6, //
    };

    Buf2D buf = {arr, 2, 3};
    ASSERTZ(buf.len() == (2 * 3));

    return 1;
}

i32 Buf2D_operator_subscript_test(void) {
    i32 arr[] = {
        1, 2, 3, //
        4, 5, 6, //
    };

    i32 rows = 2;
    i32 cols = 3;
    Buf2D<i32> buf = {arr, rows, cols};
    const Buf2D<i32> buf_const = {arr, rows, cols};

    for (i32 i = 0; i < buf.len(); ++i) {
        i32 &p = buf[i];
        const i32 &pc = buf[i];
        const i32 &pc_const = buf_const[i];

        ASSERTZ(p == arr[i]);
        ASSERTZ(pc == arr[i]);
        ASSERTZ(pc_const == arr[i]);
    }

    return 1;
}

// cpp.hpp::Arr
i32 Arr_len_test(void) {
    Arr<3, i32> arr = {0, 1, 2};
    ASSERTZ(arr.len() == 3);

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

i32 Arr_x_test(void) {
    V4i u = {3, 4, 5, 6};
    const V4i v = {4, 5, 6, 7};

    ASSERTZ(u.x() == 3);
    ASSERTZ(v.x() == 4);

    return 1;
}

i32 Arr_y_test(void) {
    V4i u = {3, 4, 5, 6};
    const V4i v = {4, 5, 6, 7};

    ASSERTZ(u.y() == 4);
    ASSERTZ(v.y() == 5);

    return 1;
}

i32 Arr_z_test(void) {
    V4i u = {3, 4, 5, 6};
    const V4i v = {4, 5, 6, 7};

    ASSERTZ(u.z() == 5);
    ASSERTZ(v.z() == 6);

    return 1;
}

i32 Arr_w_test(void) {
    V4i u = {3, 4, 5, 6};
    const V4i v = {4, 5, 6, 7};

    ASSERTZ(u.w() == 6);
    ASSERTZ(v.w() == 7);

    return 1;
}

i32 Arr_xy_test(void) {
    V4i u = {3, 4, 5, 6};
    V2i expected_xy = {3, 4};

    V2i xy = u.xy();
    ASSERTZ(xy == expected_xy);

    return 1;
}

i32 Arr_xyz_test(void) {
    V4i u = {3, 4, 5, 6};
    V3i expected_xyz = {3, 4, 5};

    V3i xyz = u.xyz();
    ASSERTZ(xyz == expected_xyz);

    return 1;
}

i32 Arr_cast_test(void) {
    V4f u = {3, 4, 5, 6};
    V4i expected_cast = {3, 4, 5, 6};

    V4i cast = u.cast<i32>();
    ASSERTZ(cast == expected_cast);

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

i32 Arr_mix_test(void) {
    V2i u = {2, 4};
    V2i v = {8, 18};
    float t = 0.4f;
    V2f expected_mix = {4.4f, 9.6f};

    V2f mix = V2i::mix(u, v, t);
    ASSERTZ(mix == expected_mix);

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

i32 Arr_operator_subscript_test(void) {
    Arr<3, i32> arr = {0, 1, 2};
    const Arr<3, i32> arr_const = {0, 1, 2};
    ASSERTZ(arr.len() == arr_const.len());

    i32 len = arr.len();
    for (i32 i = 0; i < len; ++i) {
        i32 &p = arr[i];
        const i32 &pc = arr[i];
        const i32 &pc_const = arr_const[i];

        ASSERTZ(p == arr.ptr[i]);
        ASSERTZ(pc == arr.ptr[i]);
        ASSERTZ(pc_const == arr_const.ptr[i]);
    }

    return 1;
}

i32 Arr_operator_add_i32_test(void) {
    Arr<3, i32> arr = {0, 1, 2};
    const Arr<3, i32> arr_const = {0, 1, 2};
    ASSERTZ(arr.len() == arr_const.len());

    i32 len = arr.len();
    for (i32 i = 0; i < len; ++i) {
        i32 *p = arr + i;
        const i32 *pc = arr + i;
        const i32 *pc_const = arr_const + i;

        ASSERTZ(*p == i);
        ASSERTZ(p == (arr.ptr + i));
        ASSERTZ(pc == (arr.ptr + i));
        ASSERTZ(pc_const == (arr_const.ptr + i));
    }

    return 1;
}

i32 Arr_operator_neg_test(void) {
    V2i u = {2, -3};
    V2i expected_neg = {-2, 3};

    V2i neg = -u;
    ASSERTZ(neg == expected_neg);

    return 1;
}

i32 Arr_operator_add_Arr_test(void) {
    V2i u = {2, -3};
    V2i v = {-4, 16};
    V2i expected_add = {-2, 13};

    V2i add = u + v;
    ASSERTZ(add == expected_add);

    return 1;
}

i32 Arr_operator_add_assign_test(void) {
    V2i u = {2, -3};
    V2i v = {-4, 16};
    V2i expected_add = {-2, 13};

    u += v;
    ASSERTZ(u == expected_add);

    return 1;
}

i32 Arr_operator_div_test(void) {
    V2i u = {2, -3};
    i32 scalar = 2;
    V2f expected_div = {1, -1.5f};

    V2f div = u / scalar;
    ASSERTZ(div == expected_div);

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

i32 Arr_operator_mul_test(void) {
    V2i u = {2, -3};
    float scalar = 1.5f;
    V2f expected_mul = {3.0f, -4.5f};

    V2f su = scalar * u;
    V2f us = u * scalar;
    ASSERTZ(su == expected_mul);
    ASSERTZ(us == expected_mul);

    return 1;
}

// cpp.hpp::Arr2D
i32 Arr2D_rows_test(void) {
    Arr2D<2, 3, i32> arr = {
        2, 3, 4, //
        5, 6, 7, //
    };
    ASSERTZ(arr.rows() == 2);

    return 1;
}

i32 Arr2D_cols_test(void) {
    Arr2D<2, 3, i32> arr = {
        2, 3, 4, //
        5, 6, 7, //
    };
    ASSERTZ(arr.cols() == 3);

    return 1;
}

i32 Arr2D_buf2d_test(void) {
    Arr2D<2, 3, i32> arr = {
        2, 3, 4, //
        5, 6, 7, //
    };
    const Arr2D<2, 3, i32> arr_const = {
        2, 3, 4, //
        5, 6, 7, //
    };

    Buf2D buf = arr.buf2d();
    ASSERTZ(buf.ptr == arr.ptr);
    ASSERTZ(buf.rows == arr.rows());
    ASSERTZ(buf.cols == arr.cols());

    const Buf2D buf_const = arr_const.buf2d();
    ASSERTZ(buf_const.ptr == arr_const.ptr);
    ASSERTZ(buf_const.rows == arr_const.rows());
    ASSERTZ(buf_const.cols == arr_const.cols());

    return 1;
}

// cpp.hpp::Mat
i32 Mat_n_test(void) {
    Mat<2, i32> mat = {
        0, 1, //
        2, 3, //
    };
    ASSERTZ(mat.n() == 2);

    return 1;
}

i32 Mat_len_test(void) {
    Mat<2, i32> mat = {
        0, 1, //
        2, 3, //
    };
    ASSERTZ(mat.len() == (2 * 2));

    return 1;
}

i32 Mat_det_test(void) {
    Mat<3, i32> m = {
        2,  3,  5,  //
        7,  11, 13, //
        17, 19, 23, //
    };
    i32 expected_det = -78;

    i32 det = m.det();
    ASSERTZ(det == expected_det);

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

i32 Mat_inverse_test(void) {
    Mat<3, i32> m = {
        2,  3,  5,  //
        7,  11, 13, //
        17, 19, 23, //
    };
    Mat<3, float> expected_inverse = {
        -1.0f / 13.0f,  -1.0f / 3.0f, 8.0f / 39.0f,  //
        -10.0f / 13.0f, 1.0f / 2.0f,  -3.0f / 26.0f, //
        9.0f / 13.0f,   -1.0f / 6.0f, -1.0f / 78.0f, //
    };

    Mat<3, float> inverse = m.inverse();
    ASSERTZ(inverse == expected_inverse);

    return 1;
}

i32 Mat_cofactor_test(void) {
    Mat<4, i32> m = {
        2,  3,  5,  7,  //
        11, 13, 17, 19, //
        23, 29, 31, 37, //
        41, 43, 47, 53, //
    };
    Mat<4, i32> expected_cofactor = {
        240,  -400, -520, 600,  //
        -192, -32,  614,  -370, //
        -176, 264,  -88,  0,    //
        160,  -120, -90,  70,   //
    };

    Mat<4, i32> cofactor = m.cofactor();
    ASSERTZ(cofactor == expected_cofactor);

    return 1;
}

i32 Mat_minor_test(void) {
    Mat<3, i32> m = {
        2,  3,  5,  //
        7,  11, 13, //
        17, 19, 23, //
    };
    Mat<2, i32> expected_minors[C_ARR_LEN(m.ptr)] = {
        {
            11, 13, //
            19, 23, //
        },
        {
            7, 13,  //
            17, 23, //
        },
        {
            7, 11,  //
            17, 19, //
        },
        {
            3, 5,   //
            19, 23, //
        },
        {
            2, 5,   //
            17, 23, //
        },
        {
            2, 3,   //
            17, 19, //
        },
        {
            3, 5,   //
            11, 13, //
        },
        {
            2, 5,  //
            7, 13, //
        },
        {
            2, 3,  //
            7, 11, //
        },
    };

    for (i32 i = 0, idx = 0; i < m.n(); ++i) {
        for (i32 j = 0; j < m.n(); ++j, ++idx) {
            Mat<2, i32> minor = m.minor(i, j);
            ASSERTZ(minor == expected_minors[idx]);
        }
    }

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
    ASSERTZ(mat.n() == mat_const.n());

    i32 n = mat.n();
    for (i32 i = 0, idx = 0; i < n; ++i) {
        for (i32 j = 0; j < n; ++j, ++idx) {
            i32 &p = mat.get(i, j);
            const i32 &pc = mat.get(i, j);
            const i32 &pc_const = mat_const.get(i, j);

            i32 idx = i * n + j;
            ASSERTZ(p == mat.ptr[idx]);
            ASSERTZ(pc == mat.ptr[idx]);
            ASSERTZ(pc_const == mat_const.ptr[idx]);
        }
    }

    return 1;
}

i32 Mat_getp_test(void) {
    Mat<2, i32> mat = {
        0, 1, //
        2, 3, //
    };
    const Mat<2, i32> mat_const = {
        0, 1, //
        2, 3, //
    };
    ASSERTZ(mat.n() == mat_const.n());

    i32 n = mat.n();
    for (i32 i = 0, idx = 0; i < n; ++i) {
        for (i32 j = 0; j < n; ++j, ++idx) {
            i32 *p = mat.getp(i, j);
            const i32 *pc = mat.getp(i, j);
            const i32 *pc_const = mat_const.getp(i, j);

            i32 idx = i * n + j;
            ASSERTZ(*p == idx);
            ASSERTZ(p == (mat.ptr + idx));
            ASSERTZ(pc == (mat.ptr + idx));
            ASSERTZ(pc_const == (mat_const.ptr + idx));
        }
    }

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

i32 Mat_operator_mul_Arr_test(void) {
    M2i m = {
        4, 5, //
        6, 7, //
    };
    V2i u = {2, 3};
    V2i expected_mul_mv = {23, 33};

    V2i mul_mv = m * u;
    ASSERTZ(mul_mv == expected_mul_mv);

    return 1;
}

i32 Mat_operator_add_test(void) {
    M2i m = {
        2, 3, //
        4, 5, //
    };
    M2i n = {
        6, 7, //
        8, 9, //
    };
    M2i expected_add = {
        8, 10,  //
        12, 14, //
    };

    M2i add = m + n;
    ASSERTZ(add == expected_add);

    return 1;
}

i32 Mat_operator_add_assign_test(void) {
    M2i m = {
        2, 3, //
        4, 5, //
    };
    M2i n = {
        6, 7, //
        8, 9, //
    };
    M2i expected_add = {
        8, 10,  //
        12, 14, //
    };

    m += n;
    ASSERTZ(m == expected_add);

    return 1;
}

i32 Mat_operator_mul_Mat_test(void) {
    M2i m = {
        2, 3, //
        4, 5, //
    };
    M2i n = {
        6, 7, //
        8, 9, //
    };
    M2i expected_mul_mm = {
        36, 41, //
        64, 73, //
    };

    M2i mul_mm = m * n;
    ASSERTZ(mul_mm == expected_mul_mm);

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

i32 Mat_operator_mul_test(void) {
    float scalar = 1.5f;
    Mat<2, i32> m = {
        2, -3, //
        -4, 5, //
    };
    Mat<2, float> expected_mul{
        3.0f, -4.5f, //
        -6.0f, 7.5f, //
    };

    Mat<2, float> sm = scalar * m;
    Mat<2, float> ms = m * scalar;
    ASSERTZ(sm == expected_mul);
    ASSERTZ(ms == expected_mul);

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

i32 clamp_test(void) {
    i32 a = 0;
    i32 b = 10;
    i32 mid = (b - a) / 2;

    i32 clamp_a = clamp(a - 1, a, b);
    i32 clamp_mid = clamp(mid, a, b);
    i32 clamp_b = clamp(b + 1, a, b);

    ASSERTZ(clamp_a == a);
    ASSERTZ(clamp_mid == mid);
    ASSERTZ(clamp_b == b);

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

i32 map_range_test(void) {
    float x = 0.5f;
    float a = 0.0f;
    float b = 1.0f;
    float u = -2.0f;
    float v = 8.0f;
    float expected_map = 3.0f;

    float map = map_range(x, a, b, u, v);
    ASSERTZ(eq(map, expected_map));

    return 1;
}

i32 mag_v_test(void) {
    i32 u[] = {3, 4};
    float expected_mag = 5.0f;

    float mag = mag_v(u, C_ARR_LEN(u));
    ASSERTZ(eq(mag, expected_mag));

    return 1;
}

i32 cast_v_test(void) {
    float u[] = {3, 4, 5, 6};
    i32 expected_cast[C_ARR_LEN(u)] = {3, 4, 5, 6};

    i32 cast[C_ARR_LEN(u)];
    cast_v(u, cast, C_ARR_LEN(u));
    ASSERTZ(eq_v(cast, expected_cast, C_ARR_LEN(u)));

    return 1;
}

i32 fill_v_test(void) {
    i32 x = 2;
    i32 expected_fill[] = {x, x};

    i32 fill[C_ARR_LEN(expected_fill)];
    fill_v(x, fill, C_ARR_LEN(expected_fill));
    ASSERTZ(eq_v(fill, expected_fill, C_ARR_LEN(expected_fill)));

    return 1;
}

i32 neg_v_test(void) {
    i32 u[] = {2, -3};
    i32 expected_neg[C_ARR_LEN(u)] = {-2, 3};

    i32 neg[C_ARR_LEN(u)];
    neg_v(u, neg, C_ARR_LEN(u));
    ASSERTZ(eq_v(neg, expected_neg, C_ARR_LEN(u)));

    return 1;
}

i32 norm_v_test(void) {
    i32 u[] = {3, 4};
    float mag = mag_v(u, C_ARR_LEN(u));
    float expected_norm[C_ARR_LEN(u)] = {3.0f / mag, 4.0f / mag};

    float norm[C_ARR_LEN(u)];
    norm_v(u, norm, C_ARR_LEN(u));
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

i32 add_v_test(void) {
    i32 u[] = {2, 3};
    i32 v[C_ARR_LEN(u)] = {4, 9};
    i32 expected_add[C_ARR_LEN(u)] = {6, 12};

    i32 add[C_ARR_LEN(u)];
    add_v(u, v, add, C_ARR_LEN(u));
    ASSERTZ(eq_v(add, expected_add, C_ARR_LEN(u)));

    return 1;
}

i32 sub_v_test(void) {
    i32 u[] = {2, 3};
    i32 v[C_ARR_LEN(u)] = {4, 9};
    i32 expected_sub[C_ARR_LEN(u)] = {-2, -6};

    i32 sub[C_ARR_LEN(u)];
    sub_v(u, v, sub, C_ARR_LEN(u));
    ASSERTZ(eq_v(sub, expected_sub, C_ARR_LEN(u)));

    return 1;
}

i32 mul_vs_test(void) {
    i32 u[] = {2, -3};
    float scalar = 1.5f;
    float expected_mul_vs[C_ARR_LEN(u)] = {3.0f, -4.5f};

    float mul_vs_[C_ARR_LEN(u)];
    mul_vs(scalar, u, mul_vs_, C_ARR_LEN(u));
    ASSERTZ(eq_v(mul_vs_, expected_mul_vs, C_ARR_LEN(u)));

    return 1;
}

i32 div_vs_test(void) {
    i32 u[] = {2, -3};
    i32 scalar = 2;
    float expected_div[C_ARR_LEN(u)] = {1, -1.5f};

    float div[C_ARR_LEN(u)];
    div_vs(u, scalar, div, C_ARR_LEN(u));
    ASSERTZ(eq_v(div, expected_div, C_ARR_LEN(u)));

    return 1;
}

i32 mix_v_test(void) {
    i32 u[] = {2, 4};
    i32 v[C_ARR_LEN(u)] = {8, 18};
    float t = 0.4f;
    float expected_mix[C_ARR_LEN(u)] = {4.4f, 9.6f};

    float mix[C_ARR_LEN(u)];
    mix_v(u, v, t, mix, C_ARR_LEN(u));
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
    bary_v(u, v, w, a, b, g, bary, C_ARR_LEN(u));
    ASSERTZ(eq_v(bary, expected_bary, C_ARR_LEN(u)));

    return 1;
}

i32 I_m_test(void) {
    i32 expected_I[] = {
        1, 0, //
        0, 1, //
    };

    i32 I[C_ARR_LEN(expected_I)];
    I_m(I, C_ARR_LEN(expected_I) >> 1);
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
    fill_m(x, fill, C_ARR_LEN(expected_fill) >> 1);
    ASSERTZ(eq_v(fill, expected_fill, C_ARR_LEN(expected_fill)));

    return 1;
}

i32 det_m_test(void) {
    i32 m[] = {
        2,  3,  5,  //
        7,  11, 13, //
        17, 19, 23, //
    };
    i32 expected_det = -78;

    i32 det = det_m<3, i32>(m);
    ASSERTZ(det == expected_det);

    return 1;
}

i32 det_m__0_test(void) {
    i32 m = 0;
    i32 expected_det = 1;

    i32 det = det_m<0, i32>(&m);
    ASSERTZ(det == expected_det);

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
    trans_m(m, trans, C_ARR_LEN(m) >> 1); // TODO: >> is coincidentally correct
    ASSERTZ(eq_v(trans, expected_trans, C_ARR_LEN(m)));

    return 1;
}

i32 inverse_m_test(void) {
    i32 m[] = {
        2,  3,  5,  //
        7,  11, 13, //
        17, 19, 23, //
    };
    float expected_inverse[C_ARR_LEN(m)] = {
        -1.0f / 13.0f,  -1.0f / 3.0f, 8.0f / 39.0f,  //
        -10.0f / 13.0f, 1.0f / 2.0f,  -3.0f / 26.0f, //
        9.0f / 13.0f,   -1.0f / 6.0f, -1.0f / 78.0f, //
    };

    float inverse[C_ARR_LEN(m)];
    inverse_m<3, i32>(m, inverse);
    ASSERTZ(eq_v(inverse, expected_inverse, C_ARR_LEN(m)));

    return 1;
}

i32 cofactor_m_test(void) {
    i32 m[] = {
        2,  3,  5,  7,  //
        11, 13, 17, 19, //
        23, 29, 31, 37, //
        41, 43, 47, 53, //
    };
    i32 expected_cofactor[C_ARR_LEN(m)] = {
        240,  -400, -520, 600,  //
        -192, -32,  614,  -370, //
        -176, 264,  -88,  0,    //
        160,  -120, -90,  70,   //
    };

    i32 cofactor[C_ARR_LEN(m)];
    cofactor_m<4, i32>(m, cofactor);
    ASSERTZ(eq_v(cofactor, expected_cofactor, C_ARR_LEN(m)));

    return 1;
}

i32 minor_m_test(void) {
#define N 3
#define N_MINOR 2

    i32 m[N * N] = {
        2,  3,  5,  //
        7,  11, 13, //
        17, 19, 23, //
    };
    i32 expected_minors[C_ARR_LEN(m)][N_MINOR * N_MINOR] = {
        {
            11, 13, //
            19, 23, //
        },
        {
            7, 13,  //
            17, 23, //
        },
        {
            7, 11,  //
            17, 19, //
        },
        {
            3, 5,   //
            19, 23, //
        },
        {
            2, 5,   //
            17, 23, //
        },
        {
            2, 3,   //
            17, 19, //
        },
        {
            3, 5,   //
            11, 13, //
        },
        {
            2, 5,  //
            7, 13, //
        },
        {
            2, 3,  //
            7, 11, //
        },
    };

    i32 minor[N_MINOR * N_MINOR];
    for (i32 i = 0, idx = 0; i < N; ++i) {
        for (i32 j = 0; j < N; ++j, ++idx) {
            minor_m<N, i32>(i, j, m, minor);
            ASSERTZ(eq_v(minor, expected_minors[idx], N_MINOR * N_MINOR));
        }
    }

    return 1;

#undef N
#undef N_MINOR
}

i32 mul_mv_test(void) {
    i32 m[] = {
        4, 5, //
        6, 7, //
    };
    i32 u[C_ARR_LEN(m) >> 1] = {2, 3};
    i32 expected_mul_mv[C_ARR_LEN(u)] = {23, 33};

    i32 mul_mv_[C_ARR_LEN(u)];
    mul_mv(m, u, mul_mv_, C_ARR_LEN(u));
    ASSERTZ(eq_v(mul_mv_, expected_mul_mv, C_ARR_LEN(u)));

    return 1;
}

i32 mul_mm_test(void) {
    i32 m[] = {
        2, 3, //
        4, 5, //
    };
    i32 n[C_ARR_LEN(m)] = {
        6, 7, //
        8, 9, //
    };
    i32 expected_mul_mm[C_ARR_LEN(m)] = {
        36, 41, //
        64, 73, //
    };

    {
        i32 mul_mm_[C_ARR_LEN(m)];
        mul_mm<2, i32>(m, n, mul_mm_);
        ASSERTZ(eq_v(mul_mm_, expected_mul_mm, C_ARR_LEN(m)));
    }
    {
        i32 mul_mm_[C_ARR_LEN(m)];
        mul_mm<2, i32>(m, n, mul_mm_, 1);
        ASSERTZ(eq_v(mul_mm_, expected_mul_mm, C_ARR_LEN(m)));
    }
    {
        i32 mul_mm_[C_ARR_LEN(m)];
        mul_mm<i32>(m, n, mul_mm_, C_ARR_LEN(m) >> 1, 1);
        ASSERTZ(eq_v(mul_mm_, expected_mul_mm, C_ARR_LEN(m)));
    }
    {
        i32 mul_mm_[C_ARR_LEN(m)];
        __mul_mm(m, n, mul_mm_, C_ARR_LEN(m) >> 1, 1);
        ASSERTZ(eq_v(mul_mm_, expected_mul_mm, C_ARR_LEN(m)));
    }

    return 1;
}

i32 mul_mm_many_test(void) {
#define N 2
#define CNT 3

    i32 m[CNT][N * N] = {
        {
            2, 3, //
            4, 5, //
        },
        {
            6, 7, //
            8, 9, //
        },
        {
            6, 7, //
            8, 9, //
        },
    };
    i32 n[CNT][N * N] = {
        {
            6, 7, //
            8, 9, //
        },
        {
            10, 11, //
            12, 13, //
        },
        {
            10, 11, //
            12, 13, //
        },
    };
    i32 expected_mul_mm[CNT][N * N] = {
        {
            36, 41, //
            64, 73, //
        },
        {
            144, 157, //
            188, 205, //
        },
        {
            144, 157, //
            188, 205, //
        },
    };

    i32 *m_ptr = (i32 *)m;
    i32 *n_ptr = (i32 *)n;
    i32 *expected_ptr = (i32 *)expected_mul_mm;

    {
        i32 mul_mm_[CNT][N * N];
        mul_mm<N, i32>(m_ptr, n_ptr, (i32 *)mul_mm_, CNT);
        ASSERTZ(eq_v((i32 *)mul_mm_, expected_ptr, CNT * N * N));
    }
    {
        i32 mul_mm_[CNT][N * N];
        mul_mm<i32>(m_ptr, n_ptr, (i32 *)mul_mm_, N, CNT);
        ASSERTZ(eq_v((i32 *)mul_mm_, expected_ptr, CNT * N * N));
    }
    {
        i32 mul_mm_[CNT][N * N];
        __mul_mm(m_ptr, n_ptr, (i32 *)mul_mm_, N, CNT);
        ASSERTZ(eq_v((i32 *)mul_mm_, expected_ptr, CNT * N * N));
    }

    return 1;

#undef N
#undef CNT
}

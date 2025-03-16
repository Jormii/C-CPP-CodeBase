#pragma once

#include <math.h>
#include <stdio.h>

#include <type_traits>
#include <utility>

extern "C" {
#include "c.h"
}

#pragma region macro

#define SWAP(A, B)                                                             \
    {                                                                          \
        static_assert(std::is_same<decltype(A), decltype(B)>::value);          \
        {                                                                      \
            TESTED();                                                          \
            decltype(A) __tmp__ = B;                                           \
            B = A;                                                             \
            A = __tmp__;                                                       \
        }                                                                      \
    }

#define CONST_CAST(RET_T, F, ...)                                              \
    const_cast<RET_T>(std::as_const(*this).F(__VA_ARGS__));

#pragma endregion

#pragma region struct

template <typename T>
struct Buf {
    T *const ptr;
    const i32 len;

    Buf(T *const ptr, i32 len);

    T *get(i32 idx);
    const T *get(i32 idx) const;
};

#define BUF_FROM_C_ARR(c_arr) {c_arr, C_ARR_LEN(c_arr)}

template <i32 N, typename T>
struct Arr {
    static_assert(N > 0);

    T ptr[N];

    i32 len() const;
    T *get(i32 idx);
    const T *get(i32 idx) const;

    float mag() const;
    Arr<N, float> norm() const;

    T &x();
    T &y();
    T &z();
    T &w();
    const T &x() const;
    const T &y() const;
    const T &z() const;
    const T &w() const;
    Arr<2, T> xy() const;
    Arr<3, T> xyz() const;

    template <typename V>
    Arr<N, V> cast() const;

    void print(const char *name) const;

    static Arr ones();
    static Arr zeros();

    static T dot(const Arr &u, const Arr &v);
    static Arr cross(const Arr &u, const Arr &v);

    static Arr<N, float> mix(const Arr &u, const Arr &v, float t);
    static Arr<N, float> bary(                    //
        const Arr &u, const Arr &v, const Arr &w, //
        float a, float b, float g                 //
    );

    Arr operator-() const;
    Arr<N, float> operator/(const T &rhs) const;
    Arr operator-(const Arr &rhs) const;
    bool operator==(const Arr &rhs) const;
};

using V2i = Arr<2, i32>;
using V2f = Arr<2, float>;
using V3i = Arr<3, i32>;
using V3f = Arr<3, float>;
using V4i = Arr<4, i32>;
using V4f = Arr<4, float>;

static_assert(sizeof(Arr<2, i32>) == (2 * sizeof(i32)));

template <typename T>
using V2 = Arr<2, T>;

template <typename T>
using V3 = Arr<3, T>;

template <typename T>
using V4 = Arr<4, T>;

static_assert(sizeof(V2<i32>) == (2 * sizeof(i32)));
static_assert(sizeof(V3<i32>) == (3 * sizeof(i32)));
static_assert(sizeof(V4<i32>) == (4 * sizeof(i32)));


template <i32 N, typename T>
struct Mat {
    static_assert(N > 0);

    T ptr[N * N];

    i32 len() const;
    T *get(i32 row, i32 col);
    const T *get(i32 row, i32 col) const;

    Mat trans() const;

    void print(const char *name) const;

    static Mat I();
    static Mat ones();
    static Mat zeros();

    Arr<N, T> operator*(const Arr<N, T> &rhs) const;
    Mat operator*(const Mat &rhs) const;
    bool operator==(const Mat &rhs) const;
};

using M2i = Mat<2, i32>;
using M2f = Mat<2, float>;
using M3i = Mat<3, i32>;
using M3f = Mat<3, float>;
using M4i = Mat<4, i32>;
using M4f = Mat<4, float>;

static_assert(sizeof(Mat<2, i32>) == (2 * 2 * sizeof(i32)));

template <typename T>
using M2 = Mat<2, T>;

template <typename T>
using M3 = Mat<3, T>;

template <typename T>
using M4 = Mat<4, T>;

static_assert(sizeof(M2<i32>) == (2 * 2 * sizeof(i32)));
static_assert(sizeof(M3<i32>) == (3 * 3 * sizeof(i32)));
static_assert(sizeof(M4<i32>) == (4 * 4 * sizeof(i32)));

#pragma endregion

#pragma region function

template <typename T>
T min(const T &x, const T &y);

template <typename T>
T max(const T &x, const T &y);

template <typename T>
i32 eq(const T &x, const T &y);

template <typename T, typename V>
float map_range(const T &x, const T &a, const T &b, const V &u, const V &v);

template <typename T>
float mag_v(const T *u, i32 len);

template <typename T, typename V>
[[nodiscard]] V *cast_v(const T *u, V *out, i32 len);

template <typename T>
[[nodiscard]] T *fill_v(const T &x, T *out, i32 len);

template <typename T>
[[nodiscard]] T *neg_v(const T *u, T *out, i32 len);

template <typename T>
[[nodiscard]] float *norm_v(const T *u, float *out, i32 len);

template <typename T>
T dot_v(const T *u, const T *v, i32 len);

template <typename T>
i32 eq_v(const T *u, const T *v, i32 len);

template <typename T>
[[nodiscard]] T *sub_v(const T *u, const T *v, T *out, i32 len);

template <typename T>
[[nodiscard]] float *div_vs(const T *u, const T &s, float *out, i32 len);

template <typename T>
[[nodiscard]] float *mix_v(                              //
    const T *u, const T *v, float t, float *out, i32 len //
);

template <typename T>
[[nodiscard]] float *bary_v(            //
    const T *u, const T *v, const T *w, //
    float a, float b, float g,          //
    float *out, i32 len                 //
);

template <typename T>
[[nodiscard]] T *I_m(T *out, i32 n);

template <typename T>
[[nodiscard]] T *fill_m(const T &x, T *out, i32 n);

template <typename T>
[[nodiscard]] T *trans_m(const T *m, T *out, i32 n);

template <typename T>
[[nodiscard]] T *vmult_m(const T *m, const T *u, T *out, i32 n);

template <i32 N, typename T>
[[nodiscard]] T *mmult_m(const T *m, const T *a, T *out);

template <i32 N, typename T>
[[nodiscard]] T *mmult_m(const T *m, const T *a, T *out, i32 cnt);

template <typename T>
[[nodiscard]] T *mmult_m(const T *m, const T *a, T *out, i32 n, i32 cnt);

template <typename T>
[[nodiscard]] T *__mmult_m(const T *m, const T *a, T *out, i32 n, i32 cnt);

#pragma endregion

#pragma region template implementation

template <typename T>
i32 __Buf(const Buf<T> *buf) {
    TESTED();
    C_ARR_ASSERT(buf->ptr, buf->len);
    return 1;
}

template <typename T>
Buf<T>::Buf(T *const ptr, i32 len) : ptr{ptr}, len{len} {
    TESTED();
    MUST(__Buf(this));
}

template <typename T>
T *Buf<T>::get(i32 idx) {
    TESTED();
    C_ARR_IDX_ASSERT(ptr, len, idx);

    return ptr + idx;
}

template <typename T>
const T *Buf<T>::get(i32 idx) const {
    TESTED();
    C_ARR_IDX_ASSERT(ptr, len, idx);

    return ptr + idx;
}

template <i32 N, typename T>
i32 Arr<N, T>::len() const {
    TESTED();
    return N;
}

template <i32 N, typename T>
T *Arr<N, T>::get(i32 idx) {
    TESTED();
    C_ARR_IDX_ASSERT(ptr, N, idx);

    return ptr + idx;
};

template <i32 N, typename T>
const T *Arr<N, T>::get(i32 idx) const {
    TESTED();
    C_ARR_IDX_ASSERT(ptr, N, idx);

    return ptr + idx;
}

template <i32 N, typename T>
float Arr<N, T>::mag() const {
    TESTED();
    return mag_v(ptr, N);
}

template <i32 N, typename T>
Arr<N, float> Arr<N, T>::norm() const {
    TESTED();

    Arr<N, float> norm;
    const float *out = norm_v(ptr, norm.ptr, N);
    if (out != NULL) {
        return norm;
    } else {
        return Arr<N, float>::zeros();
    }
}

template <i32 N, typename T>
T &Arr<N, T>::x() {
    TESTED();
    return CONST_CAST(T &, x);
}

template <i32 N, typename T>
const T &Arr<N, T>::x() const {
    TESTED();
    static_assert(N >= 1);

    return ptr[0];
}

template <i32 N, typename T>
T &Arr<N, T>::y() {
    TESTED();
    return CONST_CAST(T &, y);
}

template <i32 N, typename T>
const T &Arr<N, T>::y() const {
    TESTED();
    static_assert(N >= 2);

    return ptr[1];
}

template <i32 N, typename T>
T &Arr<N, T>::z() {
    TESTED();
    return CONST_CAST(T &, z);
}

template <i32 N, typename T>
const T &Arr<N, T>::z() const {
    TESTED();
    static_assert(N >= 3);

    return ptr[2];
}

template <i32 N, typename T>
T &Arr<N, T>::w() {
    TESTED();
    return CONST_CAST(T &, w);
}

template <i32 N, typename T>
const T &Arr<N, T>::w() const {
    TESTED();
    static_assert(N >= 4);

    return ptr[3];
}

template <i32 N, typename T>
Arr<2, T> Arr<N, T>::xy() const {
    TESTED();
    static_assert(N >= 2);

    return Arr<2, T>{x(), y()};
}

template <i32 N, typename T>
Arr<3, T> Arr<N, T>::xyz() const {
    TESTED();
    static_assert(N >= 3);

    return Arr<3, T>{x(), y(), z()};
}

template <i32 N, typename T>
template <typename V>
Arr<N, V> Arr<N, T>::cast() const {
    TESTED();

    Arr<N, V> arr;
    const V *out = cast_v(ptr, arr.ptr, N);
    MUST(out != NULL);

    return arr;
}

template <i32 N, typename T>
void Arr<N, T>::print(const char *name) const {
    NOTE("LEFT UNTESTED");

    printf("Arr<%ld> %s [", N, name);
    for (i32 i = 0; i < N; ++i) {
        printf("%f\t", (float)*get(i));
    }
    printf("]\n");
}

template <i32 N, typename T>
Arr<N, T> Arr<N, T>::ones() {
    TESTED();

    Arr arr;
    const T *out = fill_v((T)1, arr.ptr, N);
    MUST(out != NULL);

    return arr;
}

template <i32 N, typename T>
Arr<N, T> Arr<N, T>::zeros() {
    TESTED();

    Arr arr;
    const T *out = fill_v((T)0, arr.ptr, N);
    MUST(out != NULL);

    return arr;
}

template <i32 N, typename T>
T Arr<N, T>::dot(const Arr &u, const Arr &v) {
    TESTED();
    return dot_v(u.ptr, v.ptr, N);
}

template <i32 N, typename T>
Arr<N, T> Arr<N, T>::cross(const Arr &u, const Arr &v) {
    TESTED();
    static_assert(N == 3);

    return {
        u.ptr[1] * v.ptr[2] - u.ptr[2] * v.ptr[1],
        u.ptr[2] * v.ptr[0] - u.ptr[0] * v.ptr[2],
        u.ptr[0] * v.ptr[1] - u.ptr[1] * v.ptr[0],
    };
}

template <i32 N, typename T>
Arr<N, float> Arr<N, T>::mix(const Arr &u, const Arr &v, float t) {
    TESTED();

    Arr<N, float> mix;
    const float *out = mix_v(u.ptr, v.ptr, t, mix.ptr, N);
    if (out != NULL) {
        return mix;
    } else {
        return Arr<N, float>::zeros();
    }
}

template <i32 N, typename T>
Arr<N, float> Arr<N, T>::bary(                //
    const Arr &u, const Arr &v, const Arr &w, //
    float a, float b, float g                 //
) {
    TESTED();

    Arr<N, float> bary;
    const float *out = bary_v(u.ptr, v.ptr, w.ptr, a, b, g, bary.ptr, N);
    if (out != NULL) {
        return bary;
    } else {
        return Arr<N, float>::zeros();
    }
}

template <i32 N, typename T>
Arr<N, T> Arr<N, T>::operator-() const {
    TESTED();

    Arr neg;
    const T *out = neg_v(ptr, neg.ptr, N);
    MUST(out != NULL);

    return neg;
}

template <i32 N, typename T>
Arr<N, float> Arr<N, T>::operator/(const T &rhs) const {
    TESTED();

    Arr<N, float> div;
    const float *out = div_vs(ptr, rhs, div.ptr, N);
    if (out != NULL) {
        return div;
    } else {
        return Arr<N, float>::zeros();
    }
}

template <i32 N, typename T>
Arr<N, T> Arr<N, T>::operator-(const Arr &rhs) const {
    TESTED();

    Arr sub;
    const T *out = sub_v(ptr, rhs.ptr, sub.ptr, N);
    MUST(out != NULL);

    return sub;
}

template <i32 N, typename T>
bool Arr<N, T>::operator==(const Arr &rhs) const {
    TESTED();
    return eq_v(ptr, rhs.ptr, N);
}

template <i32 N, typename T>
i32 Mat<N, T>::len() const {
    TESTED();
    return N;
}

template <i32 N, typename T>
T *Mat<N, T>::get(i32 row, i32 col) {
    TESTED();
    C_ARR_IDX_ASSERT(ptr, N, row);
    C_ARR_IDX_ASSERT(ptr, N, col);

    return ptr + (row * N + col);
};

template <i32 N, typename T>
const T *Mat<N, T>::get(i32 row, i32 col) const {
    TESTED();
    C_ARR_IDX_ASSERT(ptr, N, row);
    C_ARR_IDX_ASSERT(ptr, N, col);

    return ptr + (row * N + col);
};

template <i32 N, typename T>
Mat<N, T> Mat<N, T>::trans() const {
    TESTED();

    Mat t;
    const T *out = trans_m(ptr, t.ptr, N);
    MUST(out != NULL);

    return t;
}

template <i32 N, typename T>
void Mat<N, T>::print(const char *name) const {
    printf("M<%ld> %s\n", N, name);
    for (i32 i = 0; i < N; ++i) {
        printf("\t[ ");
        for (i32 j = 0; j < N; ++j) {
            printf("%f\t", (float)*get(i, j));
        }
        printf("]\n");
    }
}

template <i32 N, typename T>
Mat<N, T> Mat<N, T>::I() {
    TESTED();

    Mat m;
    const T *out = I_m(m.ptr, N);
    MUST(out != NULL);

    return m;
}

template <i32 N, typename T>
Mat<N, T> Mat<N, T>::ones() {
    TESTED();

    Mat m;
    const T *out = fill_m((T)1, m.ptr, N);
    MUST(out != NULL);

    return m;
}

template <i32 N, typename T>
Mat<N, T> Mat<N, T>::zeros() {
    TESTED();

    Mat m;
    const T *out = fill_m((T)0, m.ptr, N);
    MUST(out != NULL);

    return m;
}

template <i32 N, typename T>
Arr<N, T> Mat<N, T>::operator*(const Arr<N, T> &rhs) const {
    TESTED();

    Arr<N, T> vmult;
    const T *out = vmult_m(ptr, rhs.ptr, vmult.ptr, N);
    MUST(out != NULL);

    return vmult;
}

template <i32 N, typename T>
Mat<N, T> Mat<N, T>::operator*(const Mat &rhs) const {
    TESTED();

    Mat mmult;
    const T *out = mmult_m<N, T>(ptr, rhs.ptr, mmult.ptr);
    MUST(out != NULL);

    return mmult;
}

template <i32 N, typename T>
bool Mat<N, T>::operator==(const Mat &rhs) const {
    TESTED();
    return eq_v(ptr, rhs.ptr, N);
}

template <typename T>
T min(const T &x, const T &y) {
    TESTED();
    return (x < y) ? x : y;
}

template <typename T>
T max(const T &x, const T &y) {
    TESTED();
    return (x > y) ? x : y;
}

template <typename T>
inline i32 eq(const T &x, const T &y) {
    TESTED();
    return x == y;
}

template <>
inline i32 eq<float>(const float &x, const float &y) {
    TESTED();

    float d = x - y;
    float abs = fabsf(d);
    i32 nearly_eq = abs <= __FLT_EPSILON__;

    return nearly_eq;
}

template <typename T, typename V>
float map_range(const T &x, const T &a, const T &b, const V &u, const V &v) {
    TESTED();
    ASSERTZ(x >= min(a, b));
    ASSERTZ(x <= max(a, b));
    ASSERTZ(!eq(a, b));
    ASSERTZ(!eq(u, v));

    float num = x - a;
    float den = b - a;
    float map = num / den * (v - u) + u;

    return map;
}

template <typename T>
float mag_v(const T *u, i32 len) {
    TESTED();
    C_ARR_ASSERT(u, len);

    T dot = dot_v(u, u, len);
    float mag = sqrtf((float)dot);

    return mag;
}

template <typename T, typename V>
V *cast_v(const T *u, V *out, i32 len) {
    TESTED();
    C_ARR_ASSERT(u, len);
    C_ARR_ASSERT(out, len);

    for (i32 i = 0; i < len; ++i) {
        out[i] = (V)u[i];
    }

    return out;
}

template <typename T>
T *fill_v(const T &x, T *out, i32 len) {
    TESTED();
    C_ARR_ASSERT(out, len);

    for (i32 i = 0; i < len; ++i) {
        out[i] = x;
    }

    return out;
}

template <typename T>
T *neg_v(const T *u, T *out, i32 len) {
    TESTED();
    C_ARR_ASSERT(u, len);
    C_ARR_ASSERT(out, len);

    for (i32 i = 0; i < len; ++i) {
        out[i] = -u[i];
    }

    return out;
}

template <typename T>
float *norm_v(const T *u, float *out, i32 len) {
    TESTED();
    C_ARR_ASSERT(u, len);
    C_ARR_ASSERT(out, len);

    float mag = mag_v(u, len);
    ASSERTZ(!eq(mag, 0.0f));

    for (i32 i = 0; i < len; ++i) {
        out[i] = u[i] / mag;
    }

    return out;
}

template <typename T>
T dot_v(const T *u, const T *v, i32 len) {
    TESTED();
    C_ARR_ASSERT(u, len);
    C_ARR_ASSERT(v, len);

    T dot = 0;
    for (i32 i = 0; i < len; ++i) {
        dot += u[i] * v[i];
    }

    return dot;
}

template <typename T>
i32 eq_v(const T *u, const T *v, i32 len) {
    TESTED();
    C_ARR_ASSERT(u, len);
    C_ARR_ASSERT(v, len);

    i32 eq_ = 1;
    for (i32 i = 0; eq_ && i < len; ++i) {
        eq_ &= eq(u[i], v[i]);
    }

    return eq_;
}

template <typename T>
T *sub_v(const T *u, const T *v, T *out, i32 len) {
    TESTED();
    C_ARR_ASSERT(u, len);
    C_ARR_ASSERT(v, len);
    C_ARR_ASSERT(out, len);

    for (i32 i = 0; i < len; ++i) {
        out[i] = u[i] - v[i];
    }

    return out;
}

template <typename T>
float *div_vs(const T *u, const T &s, float *out, i32 len) {
    TESTED();
    C_ARR_ASSERT(u, len);
    ASSERTZ(!eq(s, (T)0));
    C_ARR_ASSERT(out, len);

    for (i32 i = 0; i < len; ++i) {
        out[i] = (float)(u[i]) / (float)s;
    }

    return out;
}

template <typename T>
float *mix_v(const T *u, const T *v, float t, float *out, i32 len) {
    TESTED();
    C_ARR_ASSERT(u, len);
    C_ARR_ASSERT(v, len);
    ASSERTZ(t >= 0);
    ASSERTZ(t <= 1);
    C_ARR_ASSERT(out, len);

    for (i32 i = 0; i < len; ++i) {
        out[i] = (1.0f - t) * u[i] + t * v[i];
    }

    return out;
}

template <typename T>
float *bary_v(                          //
    const T *u, const T *v, const T *w, //
    float a, float b, float g,          //
    float *out, i32 len                 //
) {
    TESTED();
    C_ARR_ASSERT(u, len);
    C_ARR_ASSERT(v, len);
    C_ARR_ASSERT(w, len);
    ASSERTZ(a >= 0.0f);
    ASSERTZ(b >= 0.0f);
    ASSERTZ(g >= 0.0f);
    ASSERTZ(eq(a + b + g, 1.0f));
    C_ARR_ASSERT(out, len);

    for (i32 i = 0; i < len; ++i) {
        out[i] = a * u[i] + b * v[i] + g * w[i];
    }

    return out;
}

template <typename T>
T *I_m(T *out, i32 n) {
    TESTED();
    C_ARR_ASSERT(out, n);

    for (i32 i = 0, idx = 0; i < n; ++i) {
        for (i32 j = 0; j < n; ++j, ++idx) {
            out[idx] = (T)(i == j);
        }
    }

    return out;
}

template <typename T>
T *fill_m(const T &x, T *out, i32 n) {
    TESTED();
    return fill_v(x, out, n * n);
}

template <typename T>
T *trans_m(const T *m, T *out, i32 n) {
    TESTED();
    C_ARR_ASSERT(m, n);
    C_ARR_ASSERT(out, n);

    for (i32 i = 0; i < n; ++i) {
        for (i32 j = 0; j < n; ++j) {
            out[j * n + i] = m[i * n + j];
        }
    }

    return out;
}

template <typename T>
T *vmult_m(const T *m, const T *u, T *out, i32 n) {
    TESTED();
    C_ARR_ASSERT(m, n);
    C_ARR_ASSERT(u, n);
    C_ARR_ASSERT(out, n);

    for (i32 i = 0; i < n; ++i) {
        out[i] = dot_v(m + i * n, u, n);
    }

    return out;
}

template <i32 N, typename T>
inline T *mmult_m(const T *m, const T *a, T *out) {
    TESTED();
    return __mmult_m(m, a, out, N, 1);
}

template <i32 N, typename T>
T *mmult_m(const T *m, const T *a, T *out, i32 cnt) {
    TESTED();
    return __mmult_m(m, a, out, N, cnt);
}

template <typename T>
T *mmult_m(const T *m, const T *a, T *out, i32 n, i32 cnt) {
    TESTED();
    return __mmult_m(m, a, out, n, cnt);
}

template <typename T>
T *__mmult_m(const T *m, const T *a, T *out, i32 n, i32 cnt) {
    TESTED();
    C_ARR_ASSERT(m, n);
    C_ARR_ASSERT(a, n);
    C_ARR_ASSERT(out, n);

    i32 off = n * n;

    T *out_ptr = out;
    const T *m_ptr = m;
    const T *a_ptr = a;
    for (i32 _ = 0; _ < cnt; ++_, m_ptr += off, a_ptr += off) {
        for (i32 i = 0; i < n; ++i) {
            for (i32 j = 0; j < n; ++j, ++out_ptr) {
                T dot = 0;
                for (i32 dot_idx = 0; dot_idx < n; ++dot_idx) {
                    dot += m_ptr[i * n + dot_idx] * a_ptr[dot_idx * n + j];
                }

                *out_ptr = dot;
            }
        }
    }

    return out;
}

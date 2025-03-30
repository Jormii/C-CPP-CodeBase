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
    T *ptr;
    i32 len;

    Buf(T *ptr, i32 len);

    T *end();
    const T *end() const;

    T &operator*();
    const T &operator*() const;
    T &operator[](i32 idx);
    const T &operator[](i32 idx) const;
    T *operator+(i32 idx);
    const T *operator+(i32 idx) const;
};

#define BUF_FROM_C_ARR(c_arr) {c_arr, C_ARR_LEN(c_arr)}

template <i32 N, typename T>
struct Arr {
    static_assert(N > 0);

    T ptr[N];

    i32 len() const;
    float mag() const;
    Arr<N, float> norm() const;

    T &x();
    const T &x() const;
    T &y();
    const T &y() const;
    T &z();
    const T &z() const;
    T &w();
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

    T &operator[](i32 idx);
    const T &operator[](i32 idx) const;
    T *operator+(i32 idx);
    const T *operator+(i32 idx) const;

    Arr operator-() const;
    Arr &operator+=(const Arr &rhs);
    Arr<N, float> operator/(const T &rhs) const;
    Arr operator-(const Arr &rhs) const;
    bool operator==(const Arr &rhs) const;
};
template <typename R, i32 N, typename T>
Arr<N, R> operator*(const R &lhs, const Arr<N, T> &rhs);

template <i32 N, typename T, typename R>
Arr<N, R> operator*(const Arr<N, T> &lhs, const R &rhs);

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

    i32 n() const;
    i32 len() const;

    T det() const;
    Mat trans() const;
    Mat<N, float> inverse() const;
    Mat cofactor() const;
    Mat<N - 1, T> minor(i32 i, i32 j) const;

    T &get(i32 row, i32 col);
    const T &get(i32 row, i32 col) const;
    T *getp(i32 row, i32 col);
    const T *getp(i32 row, i32 col) const;

    void print(const char *name) const;

    static Mat I();
    static Mat ones();
    static Mat zeros();

    Arr<N, T> operator*(const Arr<N, T> &rhs) const;
    Mat operator*(const Mat &rhs) const;
    bool operator==(const Mat &rhs) const;
};
template <typename R, i32 N, typename T>
Mat<N, R> operator*(const R &lhs, const Mat<N, T> &rhs);

template <i32 N, typename T, typename R>
Mat<N, R> operator*(const Mat<N, T> &lhs, const R &rhs);

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
T clamp(const T &x, const T &a, const T &b);

template <typename T>
i32 eq(const T &x, const T &y);

template <typename T, typename V>
float map_range(const T &x, const T &a, const T &b, const V &u, const V &v);

template <typename T>
float mag_v(const T *u, i32 len);

template <typename T, typename V>
void cast_v(const T *u, V *out, i32 len);

template <typename T>
void fill_v(const T &x, T *out, i32 len);

template <typename T>
void neg_v(const T *u, T *out, i32 len);

template <typename T>
void norm_v(const T *u, float *out, i32 len);

template <typename T>
T dot_v(const T *u, const T *v, i32 len);

template <typename T>
i32 eq_v(const T *u, const T *v, i32 len);

template <typename T>
void sub_v(const T *u, const T *v, T *out, i32 len);

template <typename V, typename T>
void mul_vs(const V &s, const T *u, V *out, i32 len);

template <typename T>
void div_vs(const T *u, const T &s, float *out, i32 len);

template <typename T>
void mix_v(const T *u, const T *v, float t, float *out, i32 len);

template <typename T>
void bary_v(                            //
    const T *u, const T *v, const T *w, //
    float a, float b, float g,          //
    float *out, i32 len                 //
);

template <typename T>
void I_m(T *out, i32 n);

template <typename T>
void fill_m(const T &x, T *out, i32 n);

template <i32 N, typename T>
T det_m(const T *m);

template <typename T>
void trans_m(const T *m, T *out, i32 n);

template <i32 N, typename T>
void inverse_m(const T *m, float *out);

template <i32 N, typename T>
void cofactor_m(const T *m, T *out);

template <i32 N, typename T>
void minor_m(i32 i, i32 j, const T *m, T *out);

template <typename T>
void mul_mv(const T *m, const T *u, T *out, i32 n);

template <i32 N, typename T>
void mul_mm(const T *m, const T *a, T *out);

template <i32 N, typename T>
void mul_mm(const T *m, const T *a, T *out, i32 cnt);

template <typename T>
void mul_mm(const T *m, const T *a, T *out, i32 n, i32 cnt);

template <typename T>
void __mul_mm(const T *m, const T *a, T *out, i32 n, i32 cnt);

#pragma endregion

#pragma region template implementation

template <typename T>
Buf<T>::Buf(T *ptr, i32 len) : ptr{ptr}, len{len} {
    MUST(c_arr_check(ptr, len));
}

template <typename T>
T *Buf<T>::end() {
    return CONST_CAST(T *, end);
}

template <typename T>
const T *Buf<T>::end() const {
    MUST(c_arr_check(ptr, len));
    return ptr + len;
}

template <typename T>
T &Buf<T>::operator*() {
    return CONST_CAST(T &, operator*);
}

template <typename T>
const T &Buf<T>::operator*() const {
    MUST(c_arr_check(ptr, len));
    return *ptr;
}

template <typename T>
T &Buf<T>::operator[](i32 idx) {
    return CONST_CAST(T &, operator[], idx);
}

template <typename T>
const T &Buf<T>::operator[](i32 idx) const {
    MUST(c_arr_idx_check(ptr, len, idx));
    return ptr[idx];
}

template <typename T>
T *Buf<T>::operator+(i32 idx) {
    return CONST_CAST(T *, operator+, idx);
}

template <typename T>
const T *Buf<T>::operator+(i32 idx) const {
    MUST(c_arr_idx_check(ptr, len, idx));
    return ptr + idx;
}

template <i32 N, typename T>
i32 Arr<N, T>::len() const {
    return N;
}

template <i32 N, typename T>
float Arr<N, T>::mag() const {
    return mag_v(ptr, N);
}

template <i32 N, typename T>
Arr<N, float> Arr<N, T>::norm() const {
    Arr<N, float> norm;
    norm_v(ptr, norm.ptr, N);

    return norm;
}

template <i32 N, typename T>
T &Arr<N, T>::x() {
    return CONST_CAST(T &, x);
}

template <i32 N, typename T>
const T &Arr<N, T>::x() const {
    static_assert(N >= 1);
    return operator[](0);
}

template <i32 N, typename T>
T &Arr<N, T>::y() {
    return CONST_CAST(T &, y);
}

template <i32 N, typename T>
const T &Arr<N, T>::y() const {
    static_assert(N >= 2);
    return operator[](1);
}

template <i32 N, typename T>
T &Arr<N, T>::z() {
    return CONST_CAST(T &, z);
}

template <i32 N, typename T>
const T &Arr<N, T>::z() const {
    static_assert(N >= 3);
    return operator[](2);
}

template <i32 N, typename T>
T &Arr<N, T>::w() {
    return CONST_CAST(T &, w);
}

template <i32 N, typename T>
const T &Arr<N, T>::w() const {
    static_assert(N >= 4);
    return operator[](3);
}

template <i32 N, typename T>
Arr<2, T> Arr<N, T>::xy() const {
    static_assert(N >= 2);
    return Arr<2, T>{x(), y()};
}

template <i32 N, typename T>
Arr<3, T> Arr<N, T>::xyz() const {
    static_assert(N >= 3);
    return Arr<3, T>{x(), y(), z()};
}

template <i32 N, typename T>
template <typename V>
Arr<N, V> Arr<N, T>::cast() const {
    Arr<N, V> arr;
    cast_v(ptr, arr.ptr, N);

    return arr;
}

template <i32 N, typename T>
void Arr<N, T>::print(const char *name) const {
    MUST(name != NULL);

    printf("Arr<%ld> %s [", N, name);
    for (i32 i = 0; i < N; ++i) {
        printf("%f\t", (float)(this->operator[](i)));
    }
    printf("]\n");
}

template <i32 N, typename T>
Arr<N, T> Arr<N, T>::ones() {
    Arr arr;
    fill_v((T)1, arr.ptr, N);

    return arr;
}

template <i32 N, typename T>
Arr<N, T> Arr<N, T>::zeros() {
    Arr arr;
    fill_v((T)0, arr.ptr, N);

    return arr;
}

template <i32 N, typename T>
T Arr<N, T>::dot(const Arr &u, const Arr &v) {
    return dot_v(u.ptr, v.ptr, N);
}

template <i32 N, typename T>
Arr<N, T> Arr<N, T>::cross(const Arr &u, const Arr &v) {
    static_assert(N == 3);

    return {
        u[1] * v[2] - u[2] * v[1],
        u[2] * v[0] - u[0] * v[2],
        u[0] * v[1] - u[1] * v[0],
    };
}

template <i32 N, typename T>
Arr<N, float> Arr<N, T>::mix(const Arr &u, const Arr &v, float t) {
    Arr<N, float> mix;
    mix_v(u.ptr, v.ptr, t, mix.ptr, N);

    return mix;
}

template <i32 N, typename T>
Arr<N, float> Arr<N, T>::bary(                //
    const Arr &u, const Arr &v, const Arr &w, //
    float a, float b, float g                 //
) {
    Arr<N, float> bary;
    bary_v(u.ptr, v.ptr, w.ptr, a, b, g, bary.ptr, N);

    return bary;
}

template <i32 N, typename T>
T &Arr<N, T>::operator[](i32 idx) {
    return CONST_CAST(T &, operator[], idx);
}

template <i32 N, typename T>
const T &Arr<N, T>::operator[](i32 idx) const {
    MUST(c_arr_idx_check(ptr, N, idx));
    return ptr[idx];
}

template <i32 N, typename T>
T *Arr<N, T>::operator+(i32 idx) {
    return CONST_CAST(T *, operator+, idx);
}

template <i32 N, typename T>
const T *Arr<N, T>::operator+(i32 idx) const {
    MUST(c_arr_idx_check(ptr, N, idx));
    return ptr + idx;
}

template <i32 N, typename T>
Arr<N, T> Arr<N, T>::operator-() const {
    Arr neg;
    neg_v(ptr, neg.ptr, N);

    return neg;
}

template <i32 N, typename T>
Arr<N, T> &Arr<N, T>::operator+=(const Arr &rhs) {
    add_v(ptr, rhs.ptr, ptr, N);
    return *this;
}

template <i32 N, typename T>
Arr<N, float> Arr<N, T>::operator/(const T &rhs) const {
    Arr<N, float> div;
    div_vs(ptr, rhs, div.ptr, N);

    return div;
}

template <i32 N, typename T>
Arr<N, T> Arr<N, T>::operator-(const Arr &rhs) const {
    Arr sub;
    sub_v(ptr, rhs.ptr, sub.ptr, N);

    return sub;
}

template <i32 N, typename T>
bool Arr<N, T>::operator==(const Arr &rhs) const {
    return eq_v(ptr, rhs.ptr, N);
}

template <typename R, i32 N, typename T>
Arr<N, R> operator*(const R &lhs, const Arr<N, T> &rhs) {
    Arr<N, R> mul_vs_;
    mul_vs(lhs, rhs.ptr, mul_vs_.ptr, N);

    return mul_vs_;
}

template <i32 N, typename T, typename R>
Arr<N, R> operator*(const Arr<N, T> &lhs, const R &rhs) {
    return rhs * lhs;
}

template <i32 N, typename T>
i32 Mat<N, T>::n() const {
    return N;
}

template <i32 N, typename T>
i32 Mat<N, T>::len() const {
    return N * N;
}

template <i32 N, typename T>
T Mat<N, T>::det() const {
    return det_m<N, T>(ptr);
}

template <i32 N, typename T>
Mat<N, T> Mat<N, T>::trans() const {
    Mat t;
    trans_m(ptr, t.ptr, N);

    return t;
}

template <i32 N, typename T>
Mat<N, float> Mat<N, T>::inverse() const {
    Mat<N, float> inverse;
    inverse_m<N, T>(ptr, inverse.ptr);

    return inverse;
}

template <i32 N, typename T>
Mat<N, T> Mat<N, T>::cofactor() const {
    Mat cofactor;
    cofactor_m<N, T>(ptr, cofactor.ptr);

    return cofactor;
}

template <i32 N, typename T>
Mat<N - 1, T> Mat<N, T>::minor(i32 i, i32 j) const {
    Mat<N - 1, T> minor;
    minor_m<N, T>(i, j, ptr, minor.ptr);

    return minor;
}

template <i32 N, typename T>
T &Mat<N, T>::get(i32 row, i32 col) {
    return CONST_CAST(T &, get, row, col);
};

template <i32 N, typename T>
const T &Mat<N, T>::get(i32 row, i32 col) const {
    MUST(c_arr_idx_check(ptr, N, row));
    MUST(c_arr_idx_check(ptr, N, col));

    i32 idx = row * N + col;
    return ptr[idx];
};

template <i32 N, typename T>
T *Mat<N, T>::getp(i32 row, i32 col) {
    return CONST_CAST(T *, getp, row, col);
};

template <i32 N, typename T>
const T *Mat<N, T>::getp(i32 row, i32 col) const {
    MUST(c_arr_idx_check(ptr, N, row));
    MUST(c_arr_idx_check(ptr, N, col));

    i32 idx = row * N + col;
    return ptr + idx;
};

template <i32 N, typename T>
void Mat<N, T>::print(const char *name) const {
    printf("M<%ld> %s\n", N, name);
    for (i32 i = 0; i < N; ++i) {
        printf("\t[ ");
        for (i32 j = 0; j < N; ++j) {
            printf("%f\t", (float)get(i, j));
        }
        printf("]\n");
    }
}

template <i32 N, typename T>
Mat<N, T> Mat<N, T>::I() {
    Mat m;
    I_m(m.ptr, N);

    return m;
}

template <i32 N, typename T>
Mat<N, T> Mat<N, T>::ones() {
    Mat m;
    fill_m((T)1, m.ptr, N);

    return m;
}

template <i32 N, typename T>
Mat<N, T> Mat<N, T>::zeros() {
    Mat m;
    fill_m((T)0, m.ptr, N);

    return m;
}

template <i32 N, typename T>
Arr<N, T> Mat<N, T>::operator*(const Arr<N, T> &rhs) const {
    Arr<N, T> mul_mv_;
    mul_mv(ptr, rhs.ptr, mul_mv_.ptr, N);

    return mul_mv_;
}

template <i32 N, typename T>
Mat<N, T> Mat<N, T>::operator*(const Mat &rhs) const {
    Mat mul_mm_;
    mul_mm<N, T>(ptr, rhs.ptr, mul_mm_.ptr);

    return mul_mm_;
}

template <i32 N, typename T>
bool Mat<N, T>::operator==(const Mat &rhs) const {
    return eq_v(ptr, rhs.ptr, N);
}

template <typename R, i32 N, typename T>
Mat<N, R> operator*(const R &lhs, const Mat<N, T> &rhs) {
    Mat<N, R> mul_ms;
    mul_vs(lhs, rhs.ptr, mul_ms.ptr, N * N);

    return mul_ms;
}

template <i32 N, typename T, typename R>
Mat<N, R> operator*(const Mat<N, T> &lhs, const R &rhs) {
    return rhs * lhs;
}

template <typename T>
T min(const T &x, const T &y) {
    return (x < y) ? x : y;
}

template <typename T>
T max(const T &x, const T &y) {
    return (x > y) ? x : y;
}

template <typename T>
T clamp(const T &x, const T &a, const T &b) {
    MUST(a <= b);

    if (x <= a) {
        return a;
    } else if (x >= b) {
        return b;
    } else {
        return x;
    }
}

template <typename T>
inline i32 eq(const T &x, const T &y) {
    return x == y;
}

template <>
inline i32 eq<float>(const float &x, const float &y) {
    float d = x - y;
    float abs = fabsf(d);
    i32 nearly_eq = abs <= __FLT_EPSILON__;

    return nearly_eq;
}

template <typename T, typename V>
float map_range(const T &x, const T &a, const T &b, const V &u, const V &v) {
    MUST(x >= min(a, b));
    MUST(x <= max(a, b));
    MUST(!eq(a, b));
    MUST(!eq(u, v));

    float num = x - a;
    float den = b - a;
    float map = (num / den) * (v - u) + u;

    return map;
}

template <typename T>
float mag_v(const T *u, i32 len) {
    MUST(c_arr_check(u, len));

    T dot = dot_v(u, u, len);
    float mag = sqrtf((float)dot);

    return mag;
}

template <typename T, typename V>
void cast_v(const T *u, V *out, i32 len) {
    MUST(c_arr_check(u, len));
    MUST(c_arr_check(out, len));

    for (i32 i = 0; i < len; ++i) {
        out[i] = (V)u[i];
    }
}

template <typename T>
void fill_v(const T &x, T *out, i32 len) {
    MUST(c_arr_check(out, len));

    for (i32 i = 0; i < len; ++i) {
        out[i] = x;
    }
}

template <typename T>
void neg_v(const T *u, T *out, i32 len) {
    MUST(c_arr_check(u, len));
    MUST(c_arr_check(out, len));

    for (i32 i = 0; i < len; ++i) {
        out[i] = -u[i];
    }
}

template <typename T>
void norm_v(const T *u, float *out, i32 len) {
    MUST(c_arr_check(u, len));
    MUST(c_arr_check(out, len));

    float mag = mag_v(u, len);
    MUST(!eq(mag, 0.0f));

    for (i32 i = 0; i < len; ++i) {
        out[i] = (float)(u[i]) / mag;
    }
}

template <typename T>
T dot_v(const T *u, const T *v, i32 len) {
    MUST(c_arr_check(u, len));
    MUST(c_arr_check(v, len));

    T dot = 0;
    for (i32 i = 0; i < len; ++i) {
        dot += u[i] * v[i];
    }

    return dot;
}

template <typename T>
i32 eq_v(const T *u, const T *v, i32 len) {
    MUST(c_arr_check(u, len));
    MUST(c_arr_check(v, len));

    i32 eq_ = 1;
    for (i32 i = 0; eq_ && i < len; ++i) {
        eq_ &= eq(u[i], v[i]);
    }

    return eq_;
}

template <typename T>
void sub_v(const T *u, const T *v, T *out, i32 len) {
    MUST(c_arr_check(u, len));
    MUST(c_arr_check(v, len));
    MUST(c_arr_check(out, len));

    for (i32 i = 0; i < len; ++i) {
        out[i] = u[i] - v[i];
    }
}

template <typename V, typename T>
void mul_vs(const V &s, const T *u, V *out, i32 len) {
    MUST(c_arr_check(u, len));
    MUST(c_arr_check(out, len));

    for (i32 i = 0; i < len; ++i) {
        out[i] = s * (V)u[i];
    }
}

template <typename T>
void div_vs(const T *u, const T &s, float *out, i32 len) {
    MUST(c_arr_check(u, len));
    MUST(!eq(s, (T)0));
    MUST(c_arr_check(out, len));

    for (i32 i = 0; i < len; ++i) {
        out[i] = (float)(u[i]) / (float)s;
    }
}

template <typename T>
void mix_v(const T *u, const T *v, float t, float *out, i32 len) {
    MUST(c_arr_check(u, len));
    MUST(c_arr_check(v, len));
    MUST(t >= 0);
    MUST(t <= 1);
    MUST(c_arr_check(out, len));

    for (i32 i = 0; i < len; ++i) {
        out[i] = (1.0f - t) * (float)(u[i]) + t * float(v[i]);
    }
}

template <typename T>
void bary_v(                            //
    const T *u, const T *v, const T *w, //
    float a, float b, float g,          //
    float *out, i32 len                 //
) {
    MUST(c_arr_check(u, len));
    MUST(c_arr_check(v, len));
    MUST(c_arr_check(w, len));
    MUST(a >= 0.0f);
    MUST(b >= 0.0f);
    MUST(g >= 0.0f);
    MUST(eq(a + b + g, 1.0f));
    MUST(c_arr_check(out, len));

    for (i32 i = 0; i < len; ++i) {
        out[i] = a * (float)(u[i]) + b * (float)(v[i]) + g * (float)(w[i]);
    }
}

template <typename T>
void I_m(T *out, i32 n) {
    MUST(c_arr_check(out, n));

    for (i32 i = 0, idx = 0; i < n; ++i) {
        for (i32 j = 0; j < n; ++j, ++idx) {
            out[idx] = (T)(i == j);
        }
    }
}

template <typename T>
void fill_m(const T &x, T *out, i32 n) {
    fill_v(x, out, n * n);
}

template <i32 N, typename T>
T det_m(const T *m) {
    MUST(c_arr_check(m, N));

    if constexpr (N == 0) {
        return 1;
    } else if constexpr (N == 1) {
        return *m;
    } else {
        T det = 0;
        T minor[(N - 1) * (N - 1)];

        for (i32 i = 0, j = 0; j < N; j += 2) {
            minor_m<N, T>(i, j, m, minor);
            T minor_det = det_m<N - 1, T>(minor);

            det += m[j] * minor_det;
        }
        for (i32 i = 0, j = 1; j < N; j += 2) {
            minor_m<N, T>(i, j, m, minor);
            T minor_det = det_m<N - 1, T>(minor);

            det -= m[j] * minor_det;
        }

        return det;
    }
}

template <typename T>
void trans_m(const T *m, T *out, i32 n) {
    MUST(c_arr_check(m, n));
    MUST(c_arr_check(out, n));

    for (i32 i = 0; i < n; ++i) {
        for (i32 j = 0; j < n; ++j) {
            out[j * n + i] = m[i * n + j];
        }
    }
}

template <i32 N, typename T>
void inverse_m(const T *m, float *out) {
    MUST(c_arr_check(m, N));
    MUST(c_arr_check(out, N));

    T det = det_m<N, T>(m);
    MUST(!eq(det, (T)0));

    T adjoint[N * N];
    T cofactor[N * N];

    cofactor_m<N, T>(m, cofactor);
    trans_m(cofactor, adjoint, N);
    mul_vs<float, T>(1.0f / det, adjoint, out, N * N);
}

template <i32 N, typename T>
void cofactor_m(const T *m, T *out) {
    MUST(c_arr_check(m, N));
    MUST(c_arr_check(out, N));

    T minor[(N - 1) * (N - 1)];
    for (i32 i = 0, idx = 0; i < N; ++i) {
        for (i32 j = 0; j < N; ++j, ++idx) {
            minor_m<N, T>(i, j, m, minor);
            T minor_det = det_m<N - 1, T>(minor);

            i32 sign = ((i + j) & 1) ? -1 : 1;
            out[idx] = sign * minor_det;
        }
    }
}

template <i32 N, typename T>
void minor_m(i32 i, i32 j, const T *m, T *out) {
    MUST(c_arr_idx_check(m, N, i));
    MUST(c_arr_idx_check(m, N, j));
    MUST(c_arr_check(out, N));

    for (i32 mi = 0; mi < N; ++mi) {
        if (mi == i) {
            continue;
        }

        for (i32 mj = 0; mj < N; ++mj) {
            if (mj == j) {
                continue;
            }

            i32 out_mi = mi - (mi > i);
            i32 out_mj = mj - (mj > j);
            out[out_mi * (N - 1) + out_mj] = m[mi * N + mj];
        }
    }
}

template <typename T>
void mul_mv(const T *m, const T *u, T *out, i32 n) {
    MUST(c_arr_check(m, n));
    MUST(c_arr_check(u, n));
    MUST(c_arr_check(out, n));

    for (i32 i = 0; i < n; ++i) {
        out[i] = dot_v(m + i * n, u, n);
    }
}

template <i32 N, typename T>
inline void mul_mm(const T *m, const T *a, T *out) {
    __mul_mm(m, a, out, N, 1);
}

template <i32 N, typename T>
void mul_mm(const T *m, const T *a, T *out, i32 cnt) {
    __mul_mm(m, a, out, N, cnt);
}

template <typename T>
void mul_mm(const T *m, const T *a, T *out, i32 n, i32 cnt) {
    __mul_mm(m, a, out, n, cnt);
}

template <typename T>
void __mul_mm(const T *m, const T *a, T *out, i32 n, i32 cnt) {
    MUST(c_arr_check(m, n));
    MUST(c_arr_check(a, n));
    MUST(c_arr_check(out, n));
    MUST(cnt >= 0);

    i32 len = n * n;

    T *out_ptr = out;
    const T *m_ptr = m;
    const T *a_ptr = a;
    for (i32 _ = 0; _ < cnt; ++_, m_ptr += len, a_ptr += len) {
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
}

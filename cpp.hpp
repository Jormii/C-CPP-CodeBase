#pragma once

#include <math.h>
#include <type_traits>

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

    T *get(i32 idx);
    const T *get(i32 idx) const;

    float mag() const;
    Arr<N, float> norm() const;

    static Arr ones();
    static Arr zeros();

    static T dot(const Arr &u, const Arr &v);
    static Arr cross(const Arr &u, const Arr &v);

    static Arr<N, float> bary(                    //
        const Arr &u, const Arr &v, const Arr &w, //
        float a, float b, float g                 //
    );

    Arr operator-(const Arr &rhs) const;
    bool operator==(const Arr &rhs) const;
};

using V2i = Arr<2, i32>;
using V2f = Arr<2, float>;
using V3i = Arr<3, i32>;
using V3f = Arr<3, float>;

static_assert(sizeof(Arr<2, i32>) == (2 * sizeof(i32)));
template <typename T>
i32 eq(const T &x, const T &y);

template <typename T>
float mag_v(const T *u, i32 len);

template <typename T>
[[nodiscard]] float *norm_v(const T *u, float *out, i32 len);

template <typename T>
T dot_v(const T *u, const T *v, i32 len);

template <typename T>
i32 eq_v(const T *u, const T *v, i32 len);

template <typename T>
[[nodiscard]] T *sub_v(const T *u, const T *v, T *out, i32 len);

template <typename T>
template <typename T>
[[nodiscard]] float *bary_v(            //
    const T *u, const T *v, const T *w, //
    float a, float b, float g,          //
    float *out, i32 len                 //
);


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
    float *out = norm_v(ptr, norm.ptr, N);
    if (out != NULL) {
        return norm;
    } else {
        return Arr<N, float>::zeros();
    }
}

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
Arr<N, float> Arr<N, T>::bary(                //
    const Arr &u, const Arr &v, const Arr &w, //
    float a, float b, float g                 //
) {
    TESTED();

    Arr<N, float> bary;
    float *out = bary_v(u.ptr, v.ptr, w.ptr, a, b, g, bary.ptr, N);
    if (out != NULL) {
        return bary;
    } else {
        return Arr<N, float>::zeros();
    }
}

template <i32 N, typename T>
Arr<N, T> Arr<N, T>::operator-(const Arr &rhs) const {
    TESTED();

    Arr sub;
    T *out = sub_v(ptr, rhs.ptr, sub.ptr, N);
    if (out != NULL) {
        return sub;
    } else {
        return Arr::zeros();
    }
}

template <i32 N, typename T>
bool Arr<N, T>::operator==(const Arr &rhs) const {
    TESTED();
    return eq_v(ptr, rhs.ptr, N);
}

template <typename T>
i32 eq(const T &x, const T &y) {
    TESTED();
    return x == y;
}

template <>
i32 eq<float>(const float &x, const float &y) {
    TESTED();

    float d = x - y;
    float abs = fabsf(d);
    i32 nearly_eq = abs <= __FLT_EPSILON__;

    return nearly_eq;
}

template <typename T>
float mag_v(const T *u, i32 len) {
    TESTED();
    C_ARR_ASSERT(u, len);

    T dot = dot_v(u, u, len);
    float mag = sqrtf((float)dot);

    return mag;
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
float *bary_v(                          //
    const T *u, const T *v, const T *w, //
    float a, float b, float g,          //
    float *out, i32 len                 //
) {
    TESTED();
    C_ARR_ASSERT(u, len);
    C_ARR_ASSERT(v, len);
    C_ARR_ASSERT(w, len);
    C_ARR_ASSERT(out, len);
    ASSERTZ(eq(a + b + g, 1.0f));

    for (i32 i = 0; i < len; ++i) {
        out[i] = a * u[i] + b * v[i] + g * w[i];
    }

    return out;
}


#pragma once

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

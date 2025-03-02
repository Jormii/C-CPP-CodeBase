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

#include "c.h"

i32 c_arr_check(const void *ptr, i32 len) { return ptr != NULL && len >= 0; }

i32 c_arr_idx_check(const void *ptr, i32 len, i32 idx) {
    return c_arr_check(ptr, len) && idx >= 0 && idx < len;
}

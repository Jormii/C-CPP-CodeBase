#include <stdio.h>
#include <time.h>

#include "c.h"

i32 c_arr_check(const void *ptr, i32 len) { return ptr != NULL && len >= 0; }

i32 c_arr_idx_check(const void *ptr, i32 len, i32 idx) {
    return c_arr_check(ptr, len) && idx >= 0 && idx < len;
}

i32 c_arr_2d_idx(i32 cols, i32 row, i32 col) {
    MUST(row >= 0);
    MUST(col >= 0);

    i32 idx = (row * cols) + col;
    return idx;
}

i32 c_arr_2d_idx_check(const void *ptr, i32 rows, i32 cols, i32 row, i32 col) {
    return c_arr_idx_check(ptr, rows, row) && c_arr_idx_check(ptr, cols, col);
}

#ifdef NDEBUG
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void prof_dump() {}
void prof_kick(i32 idx) {}
void prof_stop(i32 idx) {}
void prof_rename(i32 idx, const char *name) {}
#pragma GCC diagnostic pop
#else

#define __SLOTS_LEN 8

typedef struct ProfSlot_st {
    const char *name;
    clock_t total;
    clock_t kicked;
    clock_t min, max;
    i32 kick_cnt, stop_cnt;
} ProfSlot;

static ProfSlot __slots[__SLOTS_LEN];

static ProfSlot *__slot(i32 idx) {
    MUST(c_arr_idx_check(__slots, __SLOTS_LEN, idx));
    return __slots + idx;
}

void prof_dump() {
    for (i32 i = 0; i < __SLOTS_LEN; ++i) {
        ProfSlot *s = __slot(i);

        if (s->kick_cnt != 0 || s->stop_cnt != 0) {
            const char *name = (s->name == NULL) ? "no-name" : s->name;

            printf(                                                         //
                "PROF %d (%s). %d|%d calls, %lu clocks [%lu, %lu]\n",       //
                i, name, s->kick_cnt, s->stop_cnt, s->total, s->min, s->max //
            );
        }

        s->total = 0;
        s->kick_cnt = 0;
        s->stop_cnt = 0;
    }
    printf("\n");
}

void prof_kick(i32 idx) {
    ProfSlot *s = __slot(idx);

    s->kick_cnt++;
    s->kicked = clock();
}

void prof_stop(i32 idx) {
    clock_t t = clock();
    ProfSlot *s = __slot(idx);

    clock_t elapsed = t - s->kicked;

    s->stop_cnt++;
    s->total += elapsed;

    if (s->min == 0 && s->max == 0) {
        s->min = s->max = elapsed;
    } else {
        s->min = MIN(s->min, elapsed);
        s->max = MAX(s->max, elapsed);
    }
}

void prof_rename(i32 idx, const char *name) {
    ProfSlot *s = __slot(idx);
    s->name = name;
}

#undef __SLOTS_LEN

#endif

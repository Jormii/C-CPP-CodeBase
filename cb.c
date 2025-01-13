#include <stdio.h>

#define ENDC "\033[0m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"

#define HEADER "\033[36m"
#define PASSED BOLD "\033[92m"
#define FAILED BOLD "\033[91m"

typedef int32_t i32;

// See c.h::MUST
void must_cb(const char *expr, const char *file, i32 line) {
    fprintf(stderr, "Failed MUST %s:%d: %s\n", file, line, expr);
}

// See c.h::ASSERTZ
void assertz_cb(const char *expr, const char *file, i32 line) {
    fprintf(stderr, "Failed ASSERTZ %s:%d: %s\n", file, line, expr);
}

// See c.h::ASSERTC
void assertc_cb(i32 errno, const char *expr, const char *file, i32 line) {
    fprintf(stderr, "Failed ASSERTC=%d %s:%d: %s\n", errno, file, line, expr);
}

// See compile_tests.py
void testing_started_cb(void) {}

// See compile_tests.py
void test_file_cb(const char *file) { printf(BOLD HEADER "%s\n" ENDC, file); }

// See compile_tests.py
i32 test_function_cb(i32 (*f)(void), const char *fname) {
    printf("- " HEADER "%s\n" ENDC, fname);

    i32 passed = (f() == 1) ? 1 : 0;
    if (!passed) {
        printf("-- " FAILED "X" ENDC " %s\n", fname);
    }

    return passed;
}

// See compile_tests.py
void testing_finished_cb(i32 passed, i32 failed) {
    printf(PASSED "\nPASSED:" ENDC " %d\n", passed);
    printf(FAILED "FAILED:" ENDC " %d\n", failed);
}

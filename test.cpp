#include <stdint.h>

typedef int32_t i32;

#ifdef __cplusplus
extern "C" {
#endif
extern void testing_started_cb(void);
extern void test_file_cb(const char *file);
extern i32 test_function_cb(i32 (*f)(void), const char *fname);
extern void testing_finished_cb(i32 passed, i32 failed);
#ifdef __cplusplus
}
#endif

// From ./tests/test.c
#ifdef __cplusplus
extern "C" {
#endif
extern i32 C_ARR_LEN_test(void);
extern i32 C_ARR_LEN_NULL_test(void);
extern i32 C_ARR_LEN_arg_ptr_test(void);
extern i32 C_ARR_ASSERT_ptr_is_NULL_test(void);
extern i32 C_ARR_ASSERT_len_is_negative_test(void);
extern i32 C_ARR_IDX_ASSERT_underflow_test(void);
extern i32 C_ARR_IDX_ASSERT_overflow_test(void);
#ifdef __cplusplus
}
#endif

// From ./tests/test.cpp
extern i32 SWAP_test(void);
extern i32 Buf_get_test(void);

int main(void) {
	i32 passed = 0;
	const i32 N_TESTS = 9;

	testing_started_cb();

	test_file_cb("./tests/test.c");
	passed += test_function_cb(C_ARR_LEN_test, "C_ARR_LEN_test");
	passed += test_function_cb(C_ARR_LEN_NULL_test, "C_ARR_LEN_NULL_test");
	passed += test_function_cb(C_ARR_LEN_arg_ptr_test, "C_ARR_LEN_arg_ptr_test");
	passed += test_function_cb(C_ARR_ASSERT_ptr_is_NULL_test, "C_ARR_ASSERT_ptr_is_NULL_test");
	passed += test_function_cb(C_ARR_ASSERT_len_is_negative_test, "C_ARR_ASSERT_len_is_negative_test");
	passed += test_function_cb(C_ARR_IDX_ASSERT_underflow_test, "C_ARR_IDX_ASSERT_underflow_test");
	passed += test_function_cb(C_ARR_IDX_ASSERT_overflow_test, "C_ARR_IDX_ASSERT_overflow_test");

	test_file_cb("./tests/test.cpp");
	passed += test_function_cb(SWAP_test, "SWAP_test");
	passed += test_function_cb(Buf_get_test, "Buf_get_test");

	testing_finished_cb(passed, N_TESTS - passed);

	return (passed == N_TESTS) ? 0 : 1;
}

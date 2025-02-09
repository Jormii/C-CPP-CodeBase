#include <stdint.h>

typedef int32_t i32;

extern void testing_started_cb(void);
extern void test_file_cb(const char *file);
extern i32 test_function_cb(i32 (*f)(void), const char *fname);
extern void testing_finished_cb(i32 passed, i32 failed);

// From ./tests/test.c
extern i32 C_ARR_LEN_test(void);
extern i32 C_ARR_LEN_NULL_test(void);
extern i32 C_ARR_LEN_arg_ptr_test(void);
extern i32 RES_get_test(void);
extern i32 RES_getc_test(void);
extern i32 RES_CONST_get_test(void);
extern i32 BUF_ptr_test(void);
extern i32 BUF_ptrc_test(void);
extern i32 BUF_CONST_ptrc_test(void);
extern i32 BUF_FROM_C_ARR_test(void);
extern i32 BUF_FROM_C_ARR_NULL_test(void);
extern i32 _BUF_ASSERT_ptr_is_NULL_test(void);
extern i32 _BUF_ASSERT_undeflow_test(void);
extern i32 _BUF_ASSERT_overflow_test(void);

int main(void) {
	i32 passed = 0;
	const i32 N_TESTS = 14;

	testing_started_cb();

	test_file_cb("./tests/test.c");
	passed += test_function_cb(C_ARR_LEN_test, "C_ARR_LEN_test");
	passed += test_function_cb(C_ARR_LEN_NULL_test, "C_ARR_LEN_NULL_test");
	passed += test_function_cb(C_ARR_LEN_arg_ptr_test, "C_ARR_LEN_arg_ptr_test");
	passed += test_function_cb(RES_get_test, "RES_get_test");
	passed += test_function_cb(RES_getc_test, "RES_getc_test");
	passed += test_function_cb(RES_CONST_get_test, "RES_CONST_get_test");
	passed += test_function_cb(BUF_ptr_test, "BUF_ptr_test");
	passed += test_function_cb(BUF_ptrc_test, "BUF_ptrc_test");
	passed += test_function_cb(BUF_CONST_ptrc_test, "BUF_CONST_ptrc_test");
	passed += test_function_cb(BUF_FROM_C_ARR_test, "BUF_FROM_C_ARR_test");
	passed += test_function_cb(BUF_FROM_C_ARR_NULL_test, "BUF_FROM_C_ARR_NULL_test");
	passed += test_function_cb(_BUF_ASSERT_ptr_is_NULL_test, "_BUF_ASSERT_ptr_is_NULL_test");
	passed += test_function_cb(_BUF_ASSERT_undeflow_test, "_BUF_ASSERT_undeflow_test");
	passed += test_function_cb(_BUF_ASSERT_overflow_test, "_BUF_ASSERT_overflow_test");

	testing_finished_cb(passed, N_TESTS - passed);

	return (passed == N_TESTS) ? 0 : 1;
}

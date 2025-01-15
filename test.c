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
extern i32 BUF_get_test(void);
extern i32 BUF_get_ptr_is_NULL_test(void);
extern i32 BUF_get_undeflow_test(void);
extern i32 BUF_get_overflow_test(void);
extern i32 BUF_get_out_ptr_is_NULL_test(void);
extern i32 BUF_ptr_test(void);
extern i32 BUF_ptr_ptr_is_NULL_test(void);
extern i32 BUF_ptr_undeflow_test(void);
extern i32 BUF_ptr_overflow_test(void);
extern i32 BUF_ptr_out_ptr_is_NULL_test(void);
extern i32 BUF_ptrc_test(void);
extern i32 BUF_ptrc_ptr_is_NULL_test(void);
extern i32 BUF_ptrc_undeflow_test(void);
extern i32 BUF_ptrc_overflow_test(void);
extern i32 BUF_ptrc_out_ptr_is_NULL_test(void);
extern i32 BUF_CONST_get_test(void);
extern i32 BUF_CONST_get_ptr_is_NULL_test(void);
extern i32 BUF_CONST_get_undeflow_test(void);
extern i32 BUF_CONST_get_overflow_test(void);
extern i32 BUF_CONST_get_out_ptr_is_NULL_test(void);
extern i32 BUF_CONST_ptrc_test(void);
extern i32 BUF_CONST_ptrc_ptr_is_NULL_test(void);
extern i32 BUF_CONST_ptrc_undeflow_test(void);
extern i32 BUF_CONST_ptrc_overflow_test(void);
extern i32 BUF_CONST_ptrc_out_ptr_is_NULL_test(void);
extern i32 BUF_FROM_C_ARR_test(void);
extern i32 BUF_FROM_C_ARR_NULL_test(void);

int main(void) {
	i32 passed = 0;
	const i32 N_TESTS = 30;

	testing_started_cb();

	test_file_cb("./tests/test.c");
	passed += test_function_cb(C_ARR_LEN_test, "C_ARR_LEN_test");
	passed += test_function_cb(C_ARR_LEN_NULL_test, "C_ARR_LEN_NULL_test");
	passed += test_function_cb(C_ARR_LEN_arg_ptr_test, "C_ARR_LEN_arg_ptr_test");
	passed += test_function_cb(BUF_get_test, "BUF_get_test");
	passed += test_function_cb(BUF_get_ptr_is_NULL_test, "BUF_get_ptr_is_NULL_test");
	passed += test_function_cb(BUF_get_undeflow_test, "BUF_get_undeflow_test");
	passed += test_function_cb(BUF_get_overflow_test, "BUF_get_overflow_test");
	passed += test_function_cb(BUF_get_out_ptr_is_NULL_test, "BUF_get_out_ptr_is_NULL_test");
	passed += test_function_cb(BUF_ptr_test, "BUF_ptr_test");
	passed += test_function_cb(BUF_ptr_ptr_is_NULL_test, "BUF_ptr_ptr_is_NULL_test");
	passed += test_function_cb(BUF_ptr_undeflow_test, "BUF_ptr_undeflow_test");
	passed += test_function_cb(BUF_ptr_overflow_test, "BUF_ptr_overflow_test");
	passed += test_function_cb(BUF_ptr_out_ptr_is_NULL_test, "BUF_ptr_out_ptr_is_NULL_test");
	passed += test_function_cb(BUF_ptrc_test, "BUF_ptrc_test");
	passed += test_function_cb(BUF_ptrc_ptr_is_NULL_test, "BUF_ptrc_ptr_is_NULL_test");
	passed += test_function_cb(BUF_ptrc_undeflow_test, "BUF_ptrc_undeflow_test");
	passed += test_function_cb(BUF_ptrc_overflow_test, "BUF_ptrc_overflow_test");
	passed += test_function_cb(BUF_ptrc_out_ptr_is_NULL_test, "BUF_ptrc_out_ptr_is_NULL_test");
	passed += test_function_cb(BUF_CONST_get_test, "BUF_CONST_get_test");
	passed += test_function_cb(BUF_CONST_get_ptr_is_NULL_test, "BUF_CONST_get_ptr_is_NULL_test");
	passed += test_function_cb(BUF_CONST_get_undeflow_test, "BUF_CONST_get_undeflow_test");
	passed += test_function_cb(BUF_CONST_get_overflow_test, "BUF_CONST_get_overflow_test");
	passed += test_function_cb(BUF_CONST_get_out_ptr_is_NULL_test, "BUF_CONST_get_out_ptr_is_NULL_test");
	passed += test_function_cb(BUF_CONST_ptrc_test, "BUF_CONST_ptrc_test");
	passed += test_function_cb(BUF_CONST_ptrc_ptr_is_NULL_test, "BUF_CONST_ptrc_ptr_is_NULL_test");
	passed += test_function_cb(BUF_CONST_ptrc_undeflow_test, "BUF_CONST_ptrc_undeflow_test");
	passed += test_function_cb(BUF_CONST_ptrc_overflow_test, "BUF_CONST_ptrc_overflow_test");
	passed += test_function_cb(BUF_CONST_ptrc_out_ptr_is_NULL_test, "BUF_CONST_ptrc_out_ptr_is_NULL_test");
	passed += test_function_cb(BUF_FROM_C_ARR_test, "BUF_FROM_C_ARR_test");
	passed += test_function_cb(BUF_FROM_C_ARR_NULL_test, "BUF_FROM_C_ARR_NULL_test");

	testing_finished_cb(passed, N_TESTS - passed);

	return (passed == N_TESTS) ? 0 : 1;
}

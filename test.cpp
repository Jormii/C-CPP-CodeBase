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
extern i32 Arr_len_test(void);
extern i32 Arr_get_test(void);
extern i32 Arr_mag_test(void);
extern i32 Arr_norm_test(void);
extern i32 Arr_ones_test(void);
extern i32 Arr_zeros_test(void);
extern i32 Arr_dot_test(void);
extern i32 Arr_cross_test(void);
extern i32 Arr_bary_test(void);
extern i32 Arr_operator_sub_test(void);
extern i32 Arr_operator_eq_test(void);
extern i32 Mat_len_test(void);
extern i32 Mat_get_test(void);
extern i32 Mat_trans_test(void);
extern i32 Mat_I_test(void);
extern i32 Mat_ones_test(void);
extern i32 Mat_zeros_test(void);
extern i32 Mat_operator_mult_Arr_test(void);
extern i32 Mat_operator_mult_Mat_test(void);
extern i32 Mat_operator_eq_test(void);
extern i32 min_test(void);
extern i32 max_test(void);
extern i32 eq_test(void);
extern i32 eq__float_test(void);
extern i32 mag_v_test(void);
extern i32 fill_v_test(void);
extern i32 norm_v_test(void);
extern i32 dot_v_test(void);
extern i32 eq_v_test(void);
extern i32 sub_v_test(void);
extern i32 mix_v_test(void);
extern i32 bary_v_test(void);
extern i32 I_m_test(void);
extern i32 fill_m_test(void);
extern i32 trans_m_test(void);
extern i32 vmult_m_test(void);
extern i32 mmult_m_test(void);

int main(void) {
	i32 passed = 0;
	const i32 N_TESTS = 46;

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
	passed += test_function_cb(Arr_len_test, "Arr_len_test");
	passed += test_function_cb(Arr_get_test, "Arr_get_test");
	passed += test_function_cb(Arr_mag_test, "Arr_mag_test");
	passed += test_function_cb(Arr_norm_test, "Arr_norm_test");
	passed += test_function_cb(Arr_ones_test, "Arr_ones_test");
	passed += test_function_cb(Arr_zeros_test, "Arr_zeros_test");
	passed += test_function_cb(Arr_dot_test, "Arr_dot_test");
	passed += test_function_cb(Arr_cross_test, "Arr_cross_test");
	passed += test_function_cb(Arr_bary_test, "Arr_bary_test");
	passed += test_function_cb(Arr_operator_sub_test, "Arr_operator_sub_test");
	passed += test_function_cb(Arr_operator_eq_test, "Arr_operator_eq_test");
	passed += test_function_cb(Mat_len_test, "Mat_len_test");
	passed += test_function_cb(Mat_get_test, "Mat_get_test");
	passed += test_function_cb(Mat_trans_test, "Mat_trans_test");
	passed += test_function_cb(Mat_I_test, "Mat_I_test");
	passed += test_function_cb(Mat_ones_test, "Mat_ones_test");
	passed += test_function_cb(Mat_zeros_test, "Mat_zeros_test");
	passed += test_function_cb(Mat_operator_mult_Arr_test, "Mat_operator_mult_Arr_test");
	passed += test_function_cb(Mat_operator_mult_Mat_test, "Mat_operator_mult_Mat_test");
	passed += test_function_cb(Mat_operator_eq_test, "Mat_operator_eq_test");
	passed += test_function_cb(min_test, "min_test");
	passed += test_function_cb(max_test, "max_test");
	passed += test_function_cb(eq_test, "eq_test");
	passed += test_function_cb(eq__float_test, "eq__float_test");
	passed += test_function_cb(mag_v_test, "mag_v_test");
	passed += test_function_cb(fill_v_test, "fill_v_test");
	passed += test_function_cb(norm_v_test, "norm_v_test");
	passed += test_function_cb(dot_v_test, "dot_v_test");
	passed += test_function_cb(eq_v_test, "eq_v_test");
	passed += test_function_cb(sub_v_test, "sub_v_test");
	passed += test_function_cb(mix_v_test, "mix_v_test");
	passed += test_function_cb(bary_v_test, "bary_v_test");
	passed += test_function_cb(I_m_test, "I_m_test");
	passed += test_function_cb(fill_m_test, "fill_m_test");
	passed += test_function_cb(trans_m_test, "trans_m_test");
	passed += test_function_cb(vmult_m_test, "vmult_m_test");
	passed += test_function_cb(mmult_m_test, "mmult_m_test");

	testing_finished_cb(passed, N_TESTS - passed);

	return (passed == N_TESTS) ? 0 : 1;
}

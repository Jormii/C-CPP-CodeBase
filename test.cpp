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

// From ./tests/c.c
#ifdef __cplusplus
extern "C" {
#endif
extern i32 MIN_test(void);
extern i32 MAX_test(void);
extern i32 C_ARR_LEN_test(void);
extern i32 C_ARR_LEN_NULL_test(void);
extern i32 C_ARR_LEN_arg_ptr_test(void);
extern i32 c_arr_check_test(void);
extern i32 c_arr_idx_check_test(void);
#ifdef __cplusplus
}
#endif

// From ./tests/cpp.cpp
extern i32 SWAP_test(void);
extern i32 Buf_get_test(void);
extern i32 Arr_len_test(void);
extern i32 Arr_get_test(void);
extern i32 Arr_mag_test(void);
extern i32 Arr_norm_test(void);
extern i32 Arr_x_test(void);
extern i32 Arr_y_test(void);
extern i32 Arr_z_test(void);
extern i32 Arr_w_test(void);
extern i32 Arr_xy_test(void);
extern i32 Arr_xyz_test(void);
extern i32 Arr_cast_test(void);
extern i32 Arr_ones_test(void);
extern i32 Arr_zeros_test(void);
extern i32 Arr_dot_test(void);
extern i32 Arr_cross_test(void);
extern i32 Arr_mix_test(void);
extern i32 Arr_bary_test(void);
extern i32 Arr_operator_neg_test(void);
extern i32 Arr_operator_div_test(void);
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
extern i32 map_range_test(void);
extern i32 mag_v_test(void);
extern i32 cast_v_test(void);
extern i32 fill_v_test(void);
extern i32 neg_v_test(void);
extern i32 norm_v_test(void);
extern i32 dot_v_test(void);
extern i32 eq_v_test(void);
extern i32 sub_v_test(void);
extern i32 div_vs_test(void);
extern i32 mix_v_test(void);
extern i32 bary_v_test(void);
extern i32 I_m_test(void);
extern i32 fill_m_test(void);
extern i32 trans_m_test(void);
extern i32 vmult_m_test(void);
extern i32 mmult_m_test(void);
extern i32 mmult_m_many_test(void);

int main(void) {
	i32 passed = 0;
	const i32 N_TESTS = 61;

	testing_started_cb();

	test_file_cb("./tests/c.c");
	passed += test_function_cb(MIN_test, "MIN_test");
	passed += test_function_cb(MAX_test, "MAX_test");
	passed += test_function_cb(C_ARR_LEN_test, "C_ARR_LEN_test");
	passed += test_function_cb(C_ARR_LEN_NULL_test, "C_ARR_LEN_NULL_test");
	passed += test_function_cb(C_ARR_LEN_arg_ptr_test, "C_ARR_LEN_arg_ptr_test");
	passed += test_function_cb(c_arr_check_test, "c_arr_check_test");
	passed += test_function_cb(c_arr_idx_check_test, "c_arr_idx_check_test");

	testing_finished_cb(passed, N_TESTS - passed);

	return (passed == N_TESTS) ? 0 : 1;
}

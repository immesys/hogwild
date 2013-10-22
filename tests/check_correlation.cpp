#include <stdlib.h>
#include <check.h>

#include "../src/primitives.h"
#include "../src/hw_correlation_behavioral.h"

void
setup (void)
{
    primitive_type_check_violations = 0;  
}

void
teardown (void)
{
  
}


START_TEST (test_basic)
{
    strided_buffer_t img;
    strided_buffer_t kernel;
    strided_buffer_t out;
    
    img.data = (hw_int*) malloc(3*3*sizeof(hw_int));
    kernel.data = (hw_int*) malloc(3*3*sizeof(hw_int));
    out.data = (hw_int*) malloc(5*5*sizeof(hw_int));
    img.offset = kernel.offset = out.offset = 0;
    img.column_stride = kernel.column_stride = out.column_stride = 0;
    img.row_stride = kernel.row_stride = out.row_stride = 0;
    img.ev_offset = kernel.ev_offset = out.ev_offset = 0;
    img.ev_length = kernel.ev_length = out.ev_length = 1;
    img.width = kernel.width = 3;
    img.height = kernel.height = 3;
    out.width = 5;
    out.height = 5;
    
    for (int i = 0; i < 9; i++)
    {
        img.data[i] = 1;
        kernel.data[i] = 1;
    }
    
    hw_correlate(img, kernel, out, 1);
    
    hw_int expected [] ={1,2,3,2,1,
                         2,4,6,4,2,
                         3,6,9,6,3,
                         2,4,6,4,2,
                         1,2,3,2,1};
                       
    for (int r = 0; r < 5; r++)
    {
        for (int c = 0; c < 5; c++)
        {
            ck_assert_int_eq(out.data[r*5 + c], expected[r*5 + c]);
        }
    }
}
END_TEST


//TODO moar

Suite *
correlation_suite (void)
{
  Suite *s = suite_create ("Correlation");

  /* Operators test case */
  TCase *tc_correlation = tcase_create ("Basic");
  tcase_add_checked_fixture (tc_correlation, setup, teardown);
  
  tcase_add_test (tc_correlation, test_basic);
  //tcase_add_test (tc_operators, test_p_sat_add);
  //tcase_add_test (tc_operators, test_p_sat_uadd);
   
  suite_add_tcase (s, tc_correlation);

  return s;
}

int
main (void)
{
  int number_failed;
  Suite *s = correlation_suite ();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

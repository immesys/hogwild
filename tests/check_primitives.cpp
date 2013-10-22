#include <stdlib.h>
#include <check.h>

#include "../src/primitives.h"

void
setup (void)
{
    primitive_type_check_violations = 0;  
}

void
teardown (void)
{
  
}

START_TEST (test_p_add)
{
    ck_assert_int_eq (P_ADD(1,1,3), 2);
    ck_assert_int_eq (primitive_type_check_violations, 0);
    P_ADD(3,3,3);
    ck_assert_int_eq (primitive_type_check_violations, 1);
    P_ADD(5,5,3);
    ck_assert (primitive_type_check_violations > 0);
}
END_TEST

START_TEST (test_p_sat_add)
{
    ck_assert_int_eq (P_SAT_ADD(3,3,3), 3);
    ck_assert_int_eq (primitive_type_check_violations, 0);
    ck_assert_int_eq (P_SAT_ADD(-10,-120,8),-128);
    ck_assert_int_eq (primitive_type_check_violations, 0);
    ck_assert_int_eq (P_SAT_ADD(70,70,8), 127);
    ck_assert_int_eq (primitive_type_check_violations, 0);
    
    P_SAT_ADD(100,-300,8);
    ck_assert (primitive_type_check_violations == 1);
}
END_TEST

START_TEST (test_p_sat_uadd)
{
    ck_assert_int_eq (P_SAT_UADD(3,3,3), 6);
    ck_assert_int_eq (primitive_type_check_violations, 0);
    ck_assert_int_eq (P_SAT_UADD(6,6,3), 8);
    ck_assert_int_eq (primitive_type_check_violations, 0);
    P_SAT_UADD(5,-10,8); //Neg not allowed
    ck_assert_int_eq (primitive_type_check_violations, 1);
}
END_TEST

//TODO moar

Suite *
primitives_suite (void)
{
  Suite *s = suite_create ("Primitives");

  /* Operators test case */
  TCase *tc_operators = tcase_create ("Operators");
  tcase_add_checked_fixture (tc_operators, setup, teardown);
  
  tcase_add_test (tc_operators, test_p_add);
  tcase_add_test (tc_operators, test_p_sat_add);
  tcase_add_test (tc_operators, test_p_sat_uadd);
   
  suite_add_tcase (s, tc_operators);

  return s;
}

int
main (void)
{
  int number_failed;
  Suite *s = primitives_suite ();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

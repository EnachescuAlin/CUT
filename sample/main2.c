#include <cut.h>

CUT_INCLUDE_MODULE(module1);
CUT_INCLUDE_MODULE(module2);

CUT_DEFINE_TEST(main_test1)
{
    CUT_CHECK_OPERATOR_INT32(5, !=, 5);
    CUT_CHECK_OPERATOR_INT32(3, ==, 3);
    CUT_CHECK_OPERATOR_INT32(1, !=, 1);
}

CUT_DEFINE_TEST(main_test2)
{
    CUT_CHECK_OPERATOR_INT32(5, !=, 5);
    CUT_CHECK_OPERATOR_INT32(3, ==, 3);
    CUT_CHECK_OPERATOR_INT32(1, !=, 1);
}

CUT_DEFINE_MAIN
    CUT_CALL_TEST(main_test1);

    CUT_CALL_MODULE(module1);
    CUT_CALL_MODULE(module2);

    CUT_CALL_TEST(main_test2);
CUT_END_MAIN
#include <cut.h>

CUT_DEFINE_TEST(module1_test1)
{
    CUT_CHECK(5 == 5);
    CUT_CHECK(3 == 3);
    CUT_CHECK(1 == 1);
}

CUT_DEFINE_TEST(module1_test2)
{
    CUT_CHECK_OPERATOR_INT32(5, ==, 5);
    CUT_CHECK_OPERATOR_INT32(3, ==, 3);
    CUT_CHECK_OPERATOR_INT32(1, ==, 1);
}

CUT_DEFINE_TEST(module1_test3)
{
    CUT_CHECK_OPERATOR_INT32(5, >=, 5);
    CUT_CHECK_OPERATOR_INT32(3, >=, 3);
    CUT_CHECK_OPERATOR_INT32(1, > , 1);
}

CUT_DEFINE_MODULE(module1)
    CUT_CALL_TEST(module1_test1);
    CUT_CALL_TEST(module1_test2);
    CUT_CALL_TEST(module1_test3);    
CUT_END_MODULE

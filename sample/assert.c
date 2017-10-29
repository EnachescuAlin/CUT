#include <cut.h>

CUT_DEFINE_TEST(test1)
{
    CUT_CHECK_OPERATOR_INT32(10, ==, 10);
}

CUT_DEFINE_TEST(test2)
{
    void *p = NULL;

    CUT_ASSERT(p != NULL);
}

CUT_DEFINE_TEST(test3)
{
    CUT_CHECK_OPERATOR_INT32(20, ==, 20);
}

CUT_DEFINE_MAIN
    CUT_CALL_TEST(test1);
    CUT_CALL_TEST(test2);
    CUT_CALL_TEST(test3);
CUT_END_MAIN

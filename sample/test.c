#include <cut.h>
#include <string.h>

CUT_DEFINE_TEST(test1)
{
    CUT_CHECK(strcmp("string", "string") == 0);
    CUT_CHECK(strcmp("a", "b") != 0);
}

CUT_DEFINE_TEST(test2)
{
    CUT_CHECK(1 == 1);
    CUT_CHECK(2 == 2);
    CUT_CHECK(3 == 3);
    CUT_CHECK(4 == 4);
    CUT_CHECK(5 == 5);
    CUT_CHECK(6 == 6);
    CUT_CHECK(7 == 7);
}

CUT_DEFINE_TEST(pulaMea)
{
    int x = 5;
    int *a = &x, *b = &x;
    CUT_CHECK(a == b);
}

CUT_DEFINE_MAIN
    CUT_CALL_TEST(test1);
    CUT_CALL_TEST(test2);
    CUT_CALL_TEST(pulaMea);
CUT_END_MAIN

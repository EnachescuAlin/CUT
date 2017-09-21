#include <cut.h>
#include <string.h>
#include <stdint.h>

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

CUT_DEFINE_TEST(test3)
{
    int x = 5;
    int *a = &x, *b = &x;
    CUT_CHECK(a == b);
}

int8_t GetNumber()
{
    return -100;
}

uint8_t GetUNumber()
{
    return 220;
}

int16_t GetInt16()
{
    return 15123;
}

uint16_t GetUint16()
{
    return 61234;
}

int32_t GetInt32()
{
    return -123123;
}

uint32_t GetUint32()
{
    return 123123;
}

CUT_DEFINE_TEST(test4)
{
    int8_t x = -5;
    CUT_CHECK_OPERATOR_INT8(GetNumber(), ==, x);
    CUT_CHECK_OPERATOR_INT8(GetNumber(), ==, 123);

    uint8_t y = 240;
    CUT_CHECK_OPERATOR_UINT8(GetUNumber(), ==, y);
    CUT_CHECK_OPERATOR_UINT8(GetUNumber(), ==, 222);

    CUT_CHECK_OPERATOR_INT16(GetInt16(), >=, 20000);
    CUT_CHECK_OPERATOR_UINT16(GetUint16(), <=, 20000);

    CUT_CHECK_OPERATOR_INT32(GetInt32(), >, 0);
    CUT_CHECK_OPERATOR_UINT32(GetUint32(), <, 1500);

    CUT_CHECK_OPERATOR_ADDRESS(GetUint32(), ==, 10000);
    CUT_CHECK_OPERATOR_ADDRESS(GetUint32(), <, 10000);
    CUT_CHECK_OPERATOR_ADDRESS(GetUint32(), >, 1000000);
}

CUT_DEFINE_TEST(test_string)
{
    CUT_CHECK_OPERATOR_STRING("abc", ==, "abc");

    CUT_CHECK_OPERATOR_STRING("abc", !=, "abd");
    CUT_CHECK_OPERATOR_STRING("abc", !=, "abcd");

    CUT_CHECK_OPERATOR_STRING("abc", >=, "abc");
    CUT_CHECK_OPERATOR_STRING("abd", >=, "abc");
    CUT_CHECK_OPERATOR_STRING("abcd", >=, "abc");

    CUT_CHECK_OPERATOR_STRING("abd", >, "abc");
    CUT_CHECK_OPERATOR_STRING("abcd", >, "abc");

    CUT_CHECK_OPERATOR_STRING("abc", <, "abd");
    CUT_CHECK_OPERATOR_STRING("abc", <, "abcd");

    CUT_CHECK_OPERATOR_STRING("abc", <=, "abc");
    CUT_CHECK_OPERATOR_STRING("abc", <=, "abd");
    CUT_CHECK_OPERATOR_STRING("abc", <=, "abcd");
}

CUT_DEFINE_TEST(test_string2)
{
    CUT_CHECK_OPERATOR_STRING("abc", !=, "abc");

    CUT_CHECK_OPERATOR_STRING("abc", ==, "abd");
    CUT_CHECK_OPERATOR_STRING("abc", ==, "abcd");

    CUT_CHECK_OPERATOR_STRING("abd", <=, "abc");
    CUT_CHECK_OPERATOR_STRING("abcd", <=, "abc");

    CUT_CHECK_OPERATOR_STRING("abd", <, "abc");
    CUT_CHECK_OPERATOR_STRING("abcd", <, "abc");

    CUT_CHECK_OPERATOR_STRING("abc", >, "abd");
    CUT_CHECK_OPERATOR_STRING("abc", >, "abcd");

    CUT_CHECK_OPERATOR_STRING("abc", >=, "abd");
    CUT_CHECK_OPERATOR_STRING("abc", >=, "abcd");
}

CUT_DEFINE_TEST(test_memory)
{
    int a = 1, b = 1, c = 2;

    CUT_CHECK_OPERATOR_MEMORY(&a, ==, &b, sizeof(int));

    CUT_CHECK_OPERATOR_MEMORY(&a, !=, &c, sizeof(int));
    CUT_CHECK_OPERATOR_MEMORY(&a, !=, &c, sizeof(int));

    CUT_CHECK_OPERATOR_MEMORY(&c, >=, &a, sizeof(int));
    CUT_CHECK_OPERATOR_MEMORY(&b, >=, &a, sizeof(int));

    CUT_CHECK_OPERATOR_MEMORY(&c, >, &b, sizeof(int));

    CUT_CHECK_OPERATOR_MEMORY(&a, <, &c, sizeof(int));

    CUT_CHECK_OPERATOR_MEMORY(&a, <=, &b, sizeof(int));
    CUT_CHECK_OPERATOR_MEMORY(&a, <=, &c, sizeof(int));
}

CUT_DEFINE_TEST(test_memory2)
{
    int a = 125, b = 125, c = 255;

    CUT_CHECK_OPERATOR_MEMORY(&a, !=, &b, sizeof(int));

    CUT_CHECK_OPERATOR_MEMORY(&a, ==, &c, sizeof(int));
    CUT_CHECK_OPERATOR_MEMORY(&a, ==, &c, sizeof(int));

    CUT_CHECK_OPERATOR_MEMORY(&c, <=, &a, sizeof(int));

    CUT_CHECK_OPERATOR_MEMORY(&c, <, &b, sizeof(int));

    CUT_CHECK_OPERATOR_MEMORY(&a, >, &c, sizeof(int));

    CUT_CHECK_OPERATOR_MEMORY(&a, >=, &c, sizeof(int));
}

CUT_DEFINE_MAIN
    CUT_CALL_TEST(test1);
    CUT_CALL_TEST(test2);
    CUT_CALL_TEST(test3);
    CUT_CALL_TEST(test4);
    CUT_CALL_TEST(test_string);
    CUT_CALL_TEST(test_string2);

    CUT_CALL_TEST(test_memory);
    CUT_CALL_TEST(test_memory2);
CUT_END_MAIN

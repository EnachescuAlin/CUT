#ifndef C_UNIT_TESTING_FRAMEWORK
#define C_UNIT_TESTING_FRAMEWORK

#include <stdio.h>

int CUT_FIRST_FAILED_CHECK;

#ifdef __linux__
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define NORMAL  "\x1B[0m"
#define BOLD    "\x1B[1m"
#else
#define RED     ""
#define GREEN   ""
#define NORMAL  ""
#define BOLD    ""
#endif



#define CUT_DEFINE_TEST(x)                                                      \
    void x(unsigned long long *CUT_PASSED_CHECKS,                               \
           unsigned long long *CUT_FAILED_CHECKS)



#define CUT_CALL_TEST(x)                                                        \
    do                                                                          \
    {                                                                           \
        printf("%s: ", #x);                                                     \
        CUT_FIRST_FAILED_CHECK = 0;                                             \
        x(&CUT_PASSED_CHECKS, &CUT_FAILED_CHECKS);                              \
        if (CUT_FIRST_FAILED_CHECK == 0)                                        \
        {                                                                       \
            CUT_PASSED_TESTS++;                                                 \
            printf("%s%sPASSED%s\n", GREEN, BOLD, NORMAL);                      \
        }                                                                       \
        else                                                                    \
        {                                                                       \
            CUT_FAILED_TESTS++;                                                 \
        }                                                                       \
    } while (0)



#define CUT_DEFINE_MAIN                                                         \
    int main(void)                                                              \
    {                                                                           \
        unsigned long long CUT_PASSED_CHECKS = 0, CUT_FAILED_CHECKS = 0;        \
        unsigned long long CUT_PASSED_TESTS = 0, CUT_FAILED_TESTS = 0;



#define CUT_END_MAIN                                                            \
        printf("\n");                                                           \
        printf("Failed tests:  %llu\n", CUT_FAILED_TESTS);                      \
        printf("Passed tests:  %llu\n", CUT_PASSED_TESTS);                      \
        printf("Failed checks: %llu\n", CUT_FAILED_CHECKS);                     \
        printf("Passed checks: %llu\n", CUT_PASSED_CHECKS);                     \
        return 0;                                                               \
    }                                                                           \



#define CUT_CHECK(x)                                                            \
    if (x)                                                                      \
    {                                                                           \
        (*CUT_PASSED_CHECKS)++;                                                 \
    }                                                                           \
    else                                                                        \
    {                                                                           \
        (*CUT_FAILED_CHECKS)++;                                                 \
        CUT_FIRST_FAILED_CHECK++;                                               \
        if (CUT_FIRST_FAILED_CHECK == 1)                                        \
            printf("%s%sFAILED%s\n", RED, BOLD, NORMAL);                        \
        printf("%s(%d): \"%s\" %sfailed%s\n", __FILE__, __LINE__, #x,           \
                RED, NORMAL);                                                   \
    }



#endif


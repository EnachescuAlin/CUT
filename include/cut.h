#ifndef C_UNIT_TESTING_FRAMEWORK
#define C_UNIT_TESTING_FRAMEWORK

#include <stdio.h>
#include <stdint.h>

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

#define FAILED 1
#define PASSED 0

#define CUT_DEFINE_TEST(x)                                                      \
    void x()                                                                    \



#define CUT_CALL_TEST(x)                                                        \
    do                                                                          \
    {                                                                           \
        printf("%s: ", #x);                                                     \
        CUT_resetFirstFailedCheck();                                            \
        x();                                                                    \
        if (CUT_getFirstFailedCheck() == 0)                                     \
        {                                                                       \
            CUT_incrementPassedTests();                                         \
            printf("%s%sPASSED%s\n", GREEN, BOLD, NORMAL);                      \
        }                                                                       \
        else                                                                    \
        {                                                                       \
            CUT_incrementFailedTests();                                         \
        }                                                                       \
    } while (0)



#define CUT_DEFINE_MAIN                                                         \
    int main(void)                                                              \
    {



#define CUT_END_MAIN                                                            \
        printf("\n");                                                           \
        printf("Failed tests:  %llu\n", CUT_getFailedTests());                  \
        printf("Passed tests:  %llu\n", CUT_getPassedTests());                  \
        printf("Failed checks: %llu\n", CUT_getFailedChecks());                 \
        printf("Passed checks: %llu\n", CUT_getPassedChecks());                 \
        if (CUT_getFailedTests())                                               \
        {                                                                       \
            return FAILED;                                                      \
        }                                                                       \
        return PASSED;                                                          \
    }                                                                           \



#define CUT_CHECK(x)                                                            \
    if (x)                                                                      \
    {                                                                           \
        CUT_incrementPassedChecks();                                            \
    }                                                                           \
    else                                                                        \
    {                                                                           \
        CUT_incrementFailedChecks();                                            \
        CUT_incrementFirstFailedCheck();                                        \
        if (CUT_getFirstFailedCheck() == 1)                                     \
            printf("%s%sFAILED%s\n", RED, BOLD, NORMAL);                        \
        printf("%s(%d): \"%s\" %sfailed%s\n", __FILE__, __LINE__, #x,           \
                RED, NORMAL);                                                   \
    }



#define CUT_CHECK_OPERATOR_TEMPLATE(format,                                     \
    actualValue, operator, expectedValue)                                       \
    if (tmp1 operator tmp2)                                                     \
    {                                                                           \
        CUT_incrementPassedChecks();                                            \
    }                                                                           \
    else                                                                        \
    {                                                                           \
        CUT_incrementFailedChecks();                                            \
        CUT_incrementFirstFailedCheck();                                        \
        if (CUT_getFirstFailedCheck() == 1)                                     \
            printf("%s%sFAILED%s\n", RED, BOLD, NORMAL);                        \
        printf("%s(%d): \"%s %s %s\" %sfailed%s"                                \
            " => actual value = " format                                        \
            " but expected value = " format "\n",                               \
            __FILE__, __LINE__,                                                 \
            #actualValue, #operator, #expectedValue,                            \
            RED, NORMAL,                                                        \
            tmp1, tmp2);                                                        \
    }



#define CUT_CHECK_OPERATOR_BASE(format, type,                                   \
    actualValue, operator, expectedValue)                                       \
    do                                                                          \
    {                                                                           \
        type tmp1 = (type)(actualValue);                                        \
        type tmp2 = (type)(expectedValue);                                      \
        CUT_CHECK_OPERATOR_TEMPLATE(format,                                     \
            actualValue, operator, expectedValue)                               \
    } while (0);



#define CUT_CHECK_OPERATOR_INT8(actualValue, operator, expectedValue)           \
    CUT_CHECK_OPERATOR_BASE("%hhd", int8_t,                                     \
        actualValue, operator, expectedValue)                                   \



#define CUT_CHECK_OPERATOR_UINT8(actualValue, operator, expectedValue)          \
    CUT_CHECK_OPERATOR_BASE("%hhu", uint8_t,                                    \
        actualValue, operator, expectedValue)



#define CUT_CHECK_OPERATOR_INT16(actualValue, operator, expectedValue)          \
    CUT_CHECK_OPERATOR_BASE("%hd", int16_t,                                     \
        actualValue, operator, expectedValue)



#define CUT_CHECK_OPERATOR_UINT16(actualValue, operator, expectedValue)         \
    CUT_CHECK_OPERATOR_BASE("%hu", uint16_t,                                    \
        actualValue, operator, expectedValue)



#define CUT_CHECK_OPERATOR_INT32(actualValue, operator, expectedValue)          \
    CUT_CHECK_OPERATOR_BASE("%d", int32_t,                                      \
        actualValue, operator, expectedValue)



#define CUT_CHECK_OPERATOR_UINT32(actualValue, operator, expectedValue)         \
    CUT_CHECK_OPERATOR_BASE("%u", uint32_t,                                     \
        actualValue, operator, expectedValue)



#define CUT_CHECK_OPERATOR_INT64(actualValue, operator, expectedValue)          \
    CUT_CHECK_OPERATOR_BASE("%lld", int64_t,                                    \
        actualValue, operator, expectedValue)



#define CUT_CHECK_OPERATOR_UINT64(actualValue, operator, expectedValue)         \
    CUT_CHECK_OPERATOR_BASE("%llu", uint64_t,                                   \
        actualValue, operator, expectedValue)



#define CUT_CHECK_OPERATOR_ADDRESS(actualValue, operator, expectedValue)        \
    CUT_CHECK_OPERATOR_BASE("%p", void*,                                        \
        actualValue, operator, expectedValue)



void CUT_incrementPassedChecks(void);
void CUT_incrementFailedChecks(void);
void CUT_incrementPassedTests(void);
void CUT_incrementFailedTests(void);
void CUT_incrementFirstFailedCheck(void);
void CUT_resetFirstFailedCheck(void);
int CUT_getFirstFailedCheck(void);
unsigned long long int CUT_getPassedChecks(void);
unsigned long long int CUT_getFailedChecks(void);
unsigned long long int CUT_getPassedTests(void);
unsigned long long int CUT_getFailedTests(void);

#endif


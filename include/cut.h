#ifndef C_UNIT_TESTING_FRAMEWORK
#define C_UNIT_TESTING_FRAMEWORK

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

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

#define E_OPERATOR  0
#define GT_OPERATOR 1
#define LT_OPERATOR 2
#define G_OPERATOR  3
#define L_OPERATOR  4
#define NE_OPERATOR 5

#ifndef NORMALIZE_NEW_LINE
#define NORMALIZE_NEW_LINE 1
#endif

#ifndef NORMALIZE_TAB
#define NORMALIZE_TAB 2
#endif

#define NORMALIZE_TYPE (NORMALIZE_NEW_LINE | NORMALIZE_TAB)

typedef void (*CUTTestPfn)();

#define CUT_DEFINE_TEST(x)                                                      \
    void x()                                                                    \



#define CUT_CALL_TEST(x)                                                        \
    do                                                                          \
    {                                                                           \
        CUT_setTestName(#x);                                                    \
        x();                                                                    \
        if (CUT_getTestStatus() == 0)                                           \
        {                                                                       \
            CUT_incrementPassedTests();                                         \
            CUT_lockOutput();                                                   \
            printf(#x ": %s%sPASSED%s\n", GREEN, BOLD, NORMAL);                 \
            CUT_unlockOutput();                                                 \
        }                                                                       \
        else                                                                    \
        {                                                                       \
            CUT_incrementFailedTests();                                         \
        }                                                                       \
    } while (0)



#define CUT_CALL_TEST_ASYNC(x)                                                  \
    CUT_launchAsync(#x, x);



#define CUT_DEFINE_MAIN                                                         \
    int main(void)                                                              \
    {                                                                           \
        CUT_init();



#define CUT_INCLUDE_MODULE(module)                                              \
    void module()



#define CUT_CALL_MODULE(module)                                                 \
    printf("Module: %s\n", #module);                                            \
    module();                                                                   \
    printf("Failed tests:  %llu\n", CUT_getModuleFailedTests());                \
    printf("Passed tests:  %llu\n", CUT_getModulePassedTests());                \
    printf("Failed checks: %llu\n", CUT_getModuleFailedChecks());               \
    printf("Passed checks: %llu\n\n", CUT_getModulePassedChecks());             \
    CUT_reinitModuleResult()



#define CUT_DEFINE_MODULE(module)                                               \
    void module()                                                               \
    {



#define CUT_END_MODULE                                                          \
        CUT_join();                                                             \
    }



#define CUT_END_MAIN                                                            \
        CUT_join();                                                             \
        CUT_lockOutput();                                                       \
        printf("Failed tests:  %llu\n", CUT_getFailedTests());                  \
        printf("Passed tests:  %llu\n", CUT_getPassedTests());                  \
        printf("Failed checks: %llu\n", CUT_getFailedChecks());                 \
        printf("Passed checks: %llu\n", CUT_getPassedChecks());                 \
        CUT_unlockOutput();                                                     \
        unsigned long long int failedTests = CUT_getFailedTests();              \
        CUT_uninit();                                                           \
        if (failedTests)                                                        \
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
        CUT_lockOutput();                                                       \
        if (CUT_getTestStatus() == 0)                                           \
            printf("%s: %s%sFAILED%s\n", CUT_getTestName(), RED, BOLD, NORMAL); \
        printf("%s(%d): \"%s\" %sfailed%s\n", __FILE__, __LINE__, #x,           \
                RED, NORMAL);                                                   \
        CUT_unlockOutput();                                                     \
        CUT_setTestStatus(1);                                                   \
    }


#define CUT_ASSERT(x)                                                           \
    if (x)                                                                      \
    {                                                                           \
        CUT_incrementPassedChecks();                                            \
    }                                                                           \
    else                                                                        \
    {                                                                           \
        CUT_incrementFailedChecks();                                            \
        CUT_lockOutput();                                                       \
        if (CUT_getTestStatus() == 0)                                           \
            printf("%s: %s%sFAILED%s\n", CUT_getTestName(), RED, BOLD, NORMAL); \
        printf("%s(%d): \"%s\" %sassert failed%s\n", __FILE__, __LINE__, #x,    \
                RED, NORMAL);                                                   \
        CUT_unlockOutput();                                                     \
        exit(1);                                                                \
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
        if (CUT_getTestStatus() == 0)                                           \
            printf("%s: %s%sFAILED%s\n", CUT_getTestName(), RED, BOLD, NORMAL); \
        printf("%s(%d): \"%s %s %s\" %sfailed%s"                                \
            " => actual value = " format                                        \
            " but is expected a value %s " format "\n",                         \
            __FILE__, __LINE__,                                                 \
            #actualValue, #operator, #expectedValue,                            \
            RED, NORMAL,                                                        \
            tmp1, CUT_getMessageForOperator(#operator), tmp2);                  \
        CUT_unlockOutput();                                                     \
        CUT_setTestStatus(1);                                                   \
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



#ifdef CUT_32BIT_VERSION
#define CUT_CHECK_OPERATOR_SIZE_T(actualValue, operator, expectedValue)         \
    CUT_CHECK_OPERATOR_BASE("%u", uint32_t,                                     \
        actualValue, operator, expectedValue)
#endif



#ifdef CUT_64BIT_VERSION
#define CUT_CHECK_OPERATOR_SIZE_T(actualValue, operator, expectedValue)         \
    CUT_CHECK_OPERATOR_BASE("%llu", uint64_t,                                   \
        actualValue, operator, expectedValue)
#endif



#define CUT_CHECK_OPERATOR_ADDRESS(actualValue, operator, expectedValue)        \
    CUT_CHECK_OPERATOR_BASE("%p", void*,                                        \
        actualValue, operator, expectedValue)



#define CUT_CHECK_OPERATOR_STRING(actualValue, operator, expectedValue)             \
    {                                                                               \
        int result = strcmp(actualValue, expectedValue);                            \
        int failed = 0;                                                             \
        switch (CUT_getOperatorId(#operator)) {                                     \
            case E_OPERATOR:                                                        \
                failed = result == 0 ? 0 : 1;                                       \
                break;                                                              \
            case GT_OPERATOR:                                                       \
                failed = result >= 0 ? 0 : 1;                                       \
                break;                                                              \
            case LT_OPERATOR:                                                       \
                failed = result <= 0 ? 0 : 1;                                       \
                break;                                                              \
            case G_OPERATOR:                                                        \
                failed = result > 0 ? 0 : 1;                                        \
                break;                                                              \
            case L_OPERATOR:                                                        \
                failed = result < 0 ? 0 : 1;                                        \
                break;                                                              \
            case NE_OPERATOR:                                                       \
                failed = result != 0 ? 0 : 1;                                       \
                break;                                                              \
            default:                                                                \
                failed = result == 0 ? 0 : 1;                                       \
                break;                                                              \
        }                                                                           \
        if (failed == 0)                                                            \
        {                                                                           \
            CUT_incrementPassedChecks();                                            \
        }                                                                           \
        else                                                                        \
        {                                                                           \
            char *actualValueNormalized =                                           \
                CUT_normalizeString(actualValue, NORMALIZE_TYPE);                   \
            char *expectedValueNormalized =                                         \
                CUT_normalizeString(expectedValue, NORMALIZE_TYPE);                 \
            CUT_incrementFailedChecks();                                            \
            CUT_lockOutput();                                                       \
            if (CUT_getTestStatus() == 0)                                           \
                printf("%s: %s%sFAILED%s\n", CUT_getTestName(), RED, BOLD, NORMAL); \
            printf("%s(%d): \"%s %s %s\" %sfailed%s"                                \
                " => actual value = \"%s\""                                         \
                " but is expected a value %s \"%s\"\n",                             \
                __FILE__, __LINE__,                                                 \
                #actualValue, #operator, #expectedValue,                            \
                RED, NORMAL,                                                        \
                actualValueNormalized ? actualValueNormalized : actualValue,        \
                CUT_getMessageForOperator(#operator),                               \
                expectedValueNormalized ? expectedValueNormalized : expectedValue); \
            CUT_unlockOutput();                                                     \
            CUT_setTestStatus(1);                                                   \
            CUT_freePtr(actualValueNormalized);                                     \
            CUT_freePtr(expectedValueNormalized);                                   \
        }                                                                           \
    }



#define CUT_CHECK_OPERATOR_MEMORY(actualValue, operator, expectedValue, length)     \
    {                                                                               \
        int result = memcmp(actualValue, expectedValue, length);                    \
        int failed = 0;                                                             \
        switch (CUT_getOperatorId(#operator)) {                                     \
            case E_OPERATOR:                                                        \
                failed = result == 0 ? 0 : 1;                                       \
                break;                                                              \
            case GT_OPERATOR:                                                       \
                failed = result >= 0 ? 0 : 1;                                       \
                break;                                                              \
            case LT_OPERATOR:                                                       \
                failed = result <= 0 ? 0 : 1;                                       \
                break;                                                              \
            case G_OPERATOR:                                                        \
                failed = result > 0 ? 0 : 1;                                        \
                break;                                                              \
            case L_OPERATOR:                                                        \
                failed = result < 0 ? 0 : 1;                                        \
                break;                                                              \
            case NE_OPERATOR:                                                       \
                failed = result != 0 ? 0 : 1;                                       \
                break;                                                              \
            default:                                                                \
                failed = result == 0 ? 0 : 1;                                       \
                break;                                                              \
        }                                                                           \
        if (failed == 0)                                                            \
        {                                                                           \
            CUT_incrementPassedChecks();                                            \
        }                                                                           \
        else                                                                        \
        {                                                                           \
            char *actualValueStr = CUT_memAreaToHexaString(actualValue, length);    \
            char *expectedValueStr = CUT_memAreaToHexaString(expectedValue, length);\
            CUT_incrementFailedChecks();                                            \
            CUT_lockOutput();                                                       \
            if (CUT_getTestStatus() == 0)                                           \
                printf("%s: %s%sFAILED%s\n", CUT_getTestName(), RED, BOLD, NORMAL); \
            printf("%s(%d): \"%s %s %s\" %sfailed%s"                                \
                " => actual value = \"%s\""                                         \
                " but is expected a value %s \"%s\"\n",                             \
                __FILE__, __LINE__,                                                 \
                #actualValue, #operator, #expectedValue,                            \
                RED, NORMAL, actualValueStr ? actualValueStr : "<null>",            \
                CUT_getMessageForOperator(#operator),                               \
                expectedValueStr ? expectedValueStr : "<null>");                    \
            CUT_unlockOutput();                                                     \
            CUT_setTestStatus(1);                                                   \
            CUT_freePtr(actualValueStr);                                            \
            CUT_freePtr(expectedValueStr);                                          \
        }                                                                           \
    }


#ifdef CUT_SOURCE
extern "C" {
#endif

void CUT_init(void);
void CUT_uninit(void);

void CUT_join(void);

void CUT_lockOutput(void);
void CUT_unlockOutput(void);

int CUT_getTestStatus(void);
void CUT_setTestStatus(int);

const char* CUT_getTestName(void);
void CUT_setTestName(const char*);

void CUT_launchAsync(const char*, CUTTestPfn);

void CUT_incrementPassedChecks(void);
void CUT_incrementFailedChecks(void);
void CUT_incrementPassedTests(void);
void CUT_incrementFailedTests(void);
unsigned long long int CUT_getPassedChecks(void);
unsigned long long int CUT_getFailedChecks(void);
unsigned long long int CUT_getPassedTests(void);
unsigned long long int CUT_getFailedTests(void);

unsigned long long int CUT_getModulePassedChecks(void);
unsigned long long int CUT_getModuleFailedChecks(void);
unsigned long long int CUT_getModulePassedTests(void);
unsigned long long int CUT_getModuleFailedTests(void);
void CUT_reinitModuleResult(void);

const char* CUT_getMessageForOperator(const char *op);

int CUT_getOperatorId(const char *op);

char* CUT_memAreaToHexaString(const void* ptr, size_t length);

char* CUT_normalizeString(const char* str, int normalizeType);

void CUT_freePtr(void* ptr);

#ifdef CUT_SOURCE
}
#endif

#endif


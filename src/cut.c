#include <cut.h>
#include <string.h>
#include <stdlib.h>

static unsigned long long int CUT_PASSED_CHECKS      = 0, CUT_FAILED_CHECKS = 0;
static unsigned long long int CUT_PASSED_TESTS       = 0, CUT_FAILED_TESTS  = 0;

static unsigned long long int CUT_MODULE_PASSED_CHECKS      = 0, CUT_MODULE_FAILED_CHECKS = 0;
static unsigned long long int CUT_MODULE_PASSED_TESTS       = 0, CUT_MODULE_FAILED_TESTS  = 0;

static                    int CUT_FIRST_FAILED_CHECK = 0;

void CUT_incrementPassedChecks(void)
{
    CUT_PASSED_CHECKS++;
    CUT_MODULE_PASSED_CHECKS++;
}

void CUT_incrementFailedChecks(void)
{
    CUT_FAILED_CHECKS++;
    CUT_MODULE_FAILED_CHECKS++;
}

void CUT_incrementPassedTests(void)
{
    CUT_PASSED_TESTS++;
    CUT_MODULE_PASSED_TESTS++;
}

void CUT_incrementFailedTests(void)
{
    CUT_FAILED_TESTS++;
    CUT_MODULE_FAILED_TESTS++;
}

void CUT_incrementFirstFailedCheck(void)
{
    CUT_FIRST_FAILED_CHECK++;
}

void CUT_resetFirstFailedCheck(void)
{
    CUT_FIRST_FAILED_CHECK = 0;
}

int CUT_getFirstFailedCheck(void)
{
    return CUT_FIRST_FAILED_CHECK;
}

unsigned long long int CUT_getPassedChecks(void)
{
    return CUT_PASSED_CHECKS;
}

unsigned long long int CUT_getFailedChecks(void)
{
    return CUT_FAILED_CHECKS;
}

unsigned long long int CUT_getPassedTests(void)
{
    return CUT_PASSED_TESTS;
}

unsigned long long int CUT_getFailedTests(void)
{
    return CUT_FAILED_TESTS;
}

const char* CUT_getMessageForOperator(const char *operator)
{
    static const char* operators[7][2] = {
        {"equal to",                    "=="},
        {"not equal to",                "!="},
        {"greater than or equal to",    ">="},
        {"greater than",                ">" },
        {"less than or equal to",       "<="},
        {"less than",                   "<" },
        {NULL, NULL}
    };

    if (operator == NULL)
    {
        return "<null>";
    }

    for (uint32_t i = 0; operators[i][0] != NULL; i++)
    {
        if (strcmp(operator, operators[i][1]) == 0)
        {
            return operators[i][0];
        }
    }

    return "<unknown>";
}

int CUT_getOperatorId(const char *operator)
{
    struct OperatorMap {
        const char *operator;
        int operatorId;
    };

    static struct OperatorMap operators[] = {
        {"==", E_OPERATOR},
        {">=", GT_OPERATOR},
        {"<=", LT_OPERATOR},
        {">", G_OPERATOR},
        {"<", L_OPERATOR},
        {"!=", NE_OPERATOR}
    };

    if (operator == NULL) {
        printf("CUT_getOperatorId -- error, null pointer - returned E_OPERATOR\n");
        return E_OPERATOR;
    }

    for (uint32_t i = 0; i < (sizeof(operators) / sizeof(struct OperatorMap)); i++) {
        if (strcmp(operator, operators[i].operator) == 0) {
            return operators[i].operatorId;
        }
    }

    printf("CUT_getOperatorId -- error, unknown operator [%s] - returned E_OPERATOR\n", operator);
    return E_OPERATOR;
}

char* CUT_memAreaToHexaString(const void* ptr, size_t length)
{
    if (ptr == NULL) {
        return NULL;
    }

    size_t size = length * 2 + 1;
    char *str = malloc(size);

    if (str == NULL) {
        return NULL;
    }

    static char hexaChars[] = "0123456789ABCDEF";
    const unsigned char *p = (unsigned const char*) ptr;
    size_t index = 0;

    for (size_t i = 0; i < length; i++, index += 2) {
        str[index] = hexaChars[p[i] >> 4];
        str[index + 1] = hexaChars[p[i] & 0x0F];
    }

    str[size - 1] = '\0';

    return str;
}

void CUT_freePtr(void* ptr)
{
    if (ptr != NULL) {
        free(ptr);
    }
}

unsigned long long int CUT_getModulePassedChecks(void)
{
    return CUT_MODULE_PASSED_CHECKS;
}

unsigned long long int CUT_getModuleFailedChecks(void)
{
    return CUT_MODULE_FAILED_CHECKS;
}

unsigned long long int CUT_getModulePassedTests(void)
{
    return CUT_MODULE_PASSED_TESTS;
}

unsigned long long int CUT_getModuleFailedTests(void)
{
    return CUT_MODULE_FAILED_TESTS;
}

void CUT_reinitModuleResult(void)
{
    CUT_MODULE_FAILED_CHECKS = 0;
    CUT_MODULE_PASSED_CHECKS = 0;

    CUT_MODULE_FAILED_TESTS = 0;
    CUT_MODULE_PASSED_TESTS = 0;
}

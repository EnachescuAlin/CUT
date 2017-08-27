#include <cut.h>
#include <string.h>

static unsigned long long int CUT_PASSED_CHECKS      = 0, CUT_FAILED_CHECKS = 0;
static unsigned long long int CUT_PASSED_TESTS       = 0, CUT_FAILED_TESTS  = 0;
static                    int CUT_FIRST_FAILED_CHECK = 0;

void CUT_incrementPassedChecks(void)
{
    CUT_PASSED_CHECKS++;
}

void CUT_incrementFailedChecks(void)
{
    CUT_FAILED_CHECKS++;
}

void CUT_incrementPassedTests(void)
{
    CUT_PASSED_TESTS++;
}

void CUT_incrementFailedTests(void)
{
    CUT_FAILED_TESTS++;
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

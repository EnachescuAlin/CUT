#define CUT_SOURCE

#include <cut.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <thread>
#include <pthread.h>
#include <list>

using namespace std;

static pthread_mutex_t g_outputMutex;
static pthread_mutex_t g_dataMutex;
static pthread_mutex_t g_threadsMutex;

static list<pthread_t> g_threads;
// threadId -> [name, status]
static map<thread::id, pair<string, int>> g_tests;

static unsigned long long int CUT_PASSED_CHECKS      = 0, CUT_FAILED_CHECKS = 0;
static unsigned long long int CUT_PASSED_TESTS       = 0, CUT_FAILED_TESTS  = 0;

static unsigned long long int CUT_MODULE_PASSED_CHECKS      = 0, CUT_MODULE_FAILED_CHECKS = 0;
static unsigned long long int CUT_MODULE_PASSED_TESTS       = 0, CUT_MODULE_FAILED_TESTS  = 0;

typedef pair<string, CUTTestPfn> TestInfo;

void* CUT_threadFunc(void *data)
{
    TestInfo *info = static_cast<TestInfo*>(data);

    pthread_mutex_lock(&g_dataMutex);

    g_tests[this_thread::get_id()].first = info->first;
    g_tests[this_thread::get_id()].second = 0;

    pthread_mutex_unlock(&g_dataMutex);

    info->second();

    if (CUT_getTestStatus() == 0) {
        CUT_lockOutput();
        printf("%s: %s%sPASSED%s\n", info->first.c_str(), GREEN, BOLD, NORMAL);
        CUT_unlockOutput();

        CUT_incrementPassedTests();
    } else {
        CUT_incrementFailedTests();
    }

    delete info;

    return NULL;
}

void CUT_launchAsync(const char *name, CUTTestPfn fn)
{
    pthread_t th;
    pthread_create(&th, NULL, CUT_threadFunc, static_cast<void*>(new TestInfo(name, fn)));

    pthread_mutex_lock(&g_threadsMutex);

    g_threads.push_back(th);

    pthread_mutex_unlock(&g_threadsMutex);
}

const char* CUT_getTestName(void)
{
    const char *name = NULL;

    pthread_mutex_lock(&g_dataMutex);

    name = g_tests[this_thread::get_id()].first.c_str();

    pthread_mutex_unlock(&g_dataMutex);

    return name;
}

void CUT_setTestName(const char *name)
{
    pthread_mutex_lock(&g_dataMutex);

    g_tests[this_thread::get_id()].first = name;

    pthread_mutex_unlock(&g_dataMutex);
}

void CUT_setTestStatus(int status)
{
    pthread_mutex_lock(&g_dataMutex);

    g_tests[this_thread::get_id()].second = status;

    pthread_mutex_unlock(&g_dataMutex);
}

int CUT_getTestStatus(void)
{
    int status = 0;

    pthread_mutex_lock(&g_dataMutex);

    status = g_tests[this_thread::get_id()].second;

    pthread_mutex_unlock(&g_dataMutex);

    return status;
}

void CUT_init(void)
{
    pthread_mutex_init(&g_outputMutex, NULL);
    pthread_mutex_init(&g_dataMutex, NULL);
    pthread_mutex_init(&g_threadsMutex, NULL);
}

void CUT_uninit(void)
{
    pthread_mutex_destroy(&g_outputMutex);
    pthread_mutex_destroy(&g_dataMutex);
    pthread_mutex_destroy(&g_threadsMutex);
}

void CUT_join(void)
{
    pthread_mutex_lock(&g_threadsMutex);

    for (auto& it : g_threads) {
        pthread_join(it, NULL);
    }

    g_threads.clear();
    g_tests.clear();

    pthread_mutex_unlock(&g_threadsMutex);
}

void CUT_lockOutput(void)
{
    pthread_mutex_lock(&g_outputMutex);
}

void CUT_unlockOutput(void)
{
    pthread_mutex_unlock(&g_outputMutex);
}

void CUT_incrementPassedChecks(void)
{
    pthread_mutex_lock(&g_dataMutex);

    CUT_PASSED_CHECKS++;
    CUT_MODULE_PASSED_CHECKS++;

    pthread_mutex_unlock(&g_dataMutex);
}

void CUT_incrementFailedChecks(void)
{
    pthread_mutex_lock(&g_dataMutex);

    CUT_FAILED_CHECKS++;
    CUT_MODULE_FAILED_CHECKS++;

    pthread_mutex_unlock(&g_dataMutex);
}

void CUT_incrementPassedTests(void)
{
    pthread_mutex_lock(&g_dataMutex);

    CUT_PASSED_TESTS++;
    CUT_MODULE_PASSED_TESTS++;

    pthread_mutex_unlock(&g_dataMutex);
}

void CUT_incrementFailedTests(void)
{
    pthread_mutex_lock(&g_dataMutex);

    CUT_FAILED_TESTS++;
    CUT_MODULE_FAILED_TESTS++;

    pthread_mutex_unlock(&g_dataMutex);
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

const char* CUT_getMessageForOperator(const char *op)
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

    if (op == NULL)
    {
        return "<null>";
    }

    for (uint32_t i = 0; operators[i][0] != NULL; i++)
    {
        if (strcmp(op, operators[i][1]) == 0)
        {
            return operators[i][0];
        }
    }

    return "<unknown>";
}

int CUT_getOperatorId(const char *op)
{
    struct OperatorMap {
        const char *op;
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

    if (op == NULL) {
        printf("CUT_getOperatorId -- error, null pointer - returned E_OPERATOR\n");
        return E_OPERATOR;
    }

    for (uint32_t i = 0; i < (sizeof(operators) / sizeof(struct OperatorMap)); i++) {
        if (strcmp(op, operators[i].op) == 0) {
            return operators[i].operatorId;
        }
    }

    printf("CUT_getOperatorId -- error, unknown operator [%s] - returned E_OPERATOR\n", op);
    return E_OPERATOR;
}

char* CUT_memAreaToHexaString(const void* ptr, size_t length)
{
    if (ptr == NULL) {
        return NULL;
    }

    size_t size = length * 2 + 1;
    char *str = (char*) malloc(size);

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

char* CUT_normalizeString(const char* str, int normalizeType)
{
    if (str == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t newLength = 0;
    while (str[i] != '\0') {
        i++;

        if ((normalizeType & NORMALIZE_NEW_LINE) && str[i] == '\n') {
            newLength += 2;
            continue;
        }

        if ((normalizeType & NORMALIZE_TAB) && str[i] == '\t') {
            newLength += 2;
            continue;
        }
    }

    // return NULL if there are not special chars
    if (newLength == 0) {
        return NULL;
    }

    newLength += i;

    char *ptr = (char*) malloc(newLength + 1);
    if (ptr == NULL) {
        return NULL;
    }

    i = 0;
    size_t j = 0;
    while (str[i] != '\0') {
        if ((normalizeType & NORMALIZE_NEW_LINE) && str[i] == '\n') {
            ptr[j++] = '\\';
            ptr[j++] = 'n';
            i++;
            continue;
        }

        if ((normalizeType & NORMALIZE_TAB) && str[i] == '\t') {
            ptr[j++] = '\\';
            ptr[j++] = 't';
            i++;
            continue;
        }

        ptr[j++] = str[i++];
    }

    ptr[j] = '\0';
    return ptr;
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

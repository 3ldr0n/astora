#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do {  \
        tests_run++;        \
        if (!(test)) {      \
            FAIL();         \
            return 1;       \
        } else {            \
            tests_passed++; \
        }                   \
    } while(0)

int tests_run = 0;
int tests_passed = 0;

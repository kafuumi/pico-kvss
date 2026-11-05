#if !defined(KVSS_TEST_ASSERT_H_)
#define KVSS_TEST_ASSERT_H_

#include <inttypes.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

extern jmp_buf kvss_test_jmp;
extern int kvss_test_failures;

void kvss_test_fail(const char *file, int line, const char *fmt, ...);

#define zassert_true(cond, ...)                                                                                        \
    do {                                                                                                               \
        if (!(cond)) {                                                                                                 \
            kvss_test_fail(__FILE__, __LINE__, __VA_ARGS__);                                                           \
        }                                                                                                              \
    } while (0)

#define zassert_ok(cond, ...) zassert_true((cond) == 0, __VA_ARGS__)

#define zassert_equal(a, b, ...)                                                                                       \
    do {                                                                                                               \
        intmax_t _a = (intmax_t)(a);                                                                                   \
        intmax_t _b = (intmax_t)(b);                                                                                   \
        if (_a != _b) {                                                                                                \
            kvss_test_fail(__FILE__, __LINE__, __VA_ARGS__);                                                           \
        }                                                                                                              \
    } while (0)

#define zassert_mem_equal(a, b, len, ...)                                                                              \
    do {                                                                                                               \
        if (memcmp((a), (b), (len)) != 0) {                                                                            \
            kvss_test_fail(__FILE__, __LINE__, __VA_ARGS__);                                                           \
        }                                                                                                              \
    } while (0)

#define zassert_between_inclusive(value, low, high, ...)                                                               \
    do {                                                                                                               \
        intmax_t _v = (intmax_t)(value);                                                                               \
        if ((_v < (intmax_t)(low)) || (_v > (intmax_t)(high))) {                                                       \
            kvss_test_fail(__FILE__, __LINE__, __VA_ARGS__);                                                           \
        }                                                                                                              \
    } while (0)

#define TC_PRINT(...) printf(__VA_ARGS__)

#endif /* KVSS_TEST_ASSERT_H_ */

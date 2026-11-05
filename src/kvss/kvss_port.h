#if !defined(KVSS_PORT_H_)
#define KVSS_PORT_H_

/*
 * Portability helpers replacing the definitions normally provided by
 * <zephyr/toolchain.h>.
 */

#if !defined(__packed)
#define __packed __attribute__((packed))
#endif

#if !defined(__unused)
#define __unused __attribute__((unused))
#endif

#if !defined(BUILD_ASSERT)
#define BUILD_ASSERT(cond, ...) _Static_assert(cond, "" __VA_ARGS__)
#endif

/*
 * Storage class for internal functions that unit tests need to reach.
 * CONFIG_ZTEST may be undefined or defined to 0; both mean disabled.
 */
#if defined(CONFIG_ZTEST) && CONFIG_ZTEST
#define KVSS_TESTABLE_STATIC
#else
#define KVSS_TESTABLE_STATIC static
#endif

/*
 * Logging used by NVS and ZMS.
 *
 * Define KVSS_PORT_LOG_IMPL and provide LOG_DBG/LOG_INF/LOG_WRN/LOG_ERR
 * yourself to route logs to a different backend (or to disable them).
 */
#if !defined(KVSS_PORT_LOG_IMPL)
#include <stdio.h>
#define LOG_DBG printf
#define LOG_ERR printf
#define LOG_INF printf
#define LOG_WRN printf
#endif

#endif /* KVSS_PORT_H_ */

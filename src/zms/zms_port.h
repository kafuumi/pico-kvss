#if !defined(ZMS_PORT_H_)
#define ZMS_PORT_H_

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(ZMS_PORT_LOG_IMPL)
#include <stdio.h>
#define LOG_DBG printf
#define LOG_ERR printf
#define LOG_INF printf
#define LOG_WRN printf
#endif

#ifdef __cplusplus
}
#endif

#endif /* ZMS_PORT_H_ */

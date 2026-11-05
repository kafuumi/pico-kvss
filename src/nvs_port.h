#if !defined(NVS_PORT_H_)
#define NVS_PORT_H_

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(NVS_PORT_LOG_IMPL)
#include <stdio.h>
#define LOG_DBG printf
#define LOG_ERR printf
#define LOG_INF printf
#endif

#ifdef __cplusplus
}
#endif

#endif /* NVS_PORT_H_ */
#if !defined(KVSS_TEST_SILENT_LOG_H_)
#define KVSS_TEST_SILENT_LOG_H_

/*
 * Test builds define KVSS_PORT_LOG_IMPL, so kvss_port.h does not provide the
 * logging macros. Force-include this header to keep the test output clean.
 */
#define LOG_DBG(...) ((void)0)
#define LOG_INF(...) ((void)0)
#define LOG_WRN(...) ((void)0)
#define LOG_ERR(...) ((void)0)

#endif /* KVSS_TEST_SILENT_LOG_H_ */

#if !defined(KVSS_TEST_FLASH_SIM_H_)
#define KVSS_TEST_FLASH_SIM_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "kvss/kvss_hal.h"

#define KVSS_TEST_MAX_SECTOR_COUNT 8U
#define KVSS_TEST_MAX_SECTOR_SIZE (64U * 1024U)

struct flash_sim_stats {
    uint32_t flash_write_calls;
    uint32_t flash_erase_calls;
};

struct flash_sim_thresholds {
    uint32_t max_write_calls;
    uint32_t max_erase_calls;
    uint32_t max_len;
};

extern struct flash_sim_stats flash_sim_stats;
extern struct flash_sim_thresholds flash_sim_thresholds;
extern bool flash_sim_explicit_erase;

int kvss_test_flash_init(uint32_t sector_size, uint32_t sector_count, uint32_t write_block_size,
                         uint8_t erase_value, bool explicit_erase);
void kvss_test_flash_reset(void);

struct flash_parameters *kvss_test_flash_parameters(void);
struct kvss_hal_flash kvss_test_flash_device(void);
struct kvss_hal_mutex kvss_test_mutex(void);

#endif /* KVSS_TEST_FLASH_SIM_H_ */

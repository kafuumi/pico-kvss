#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "flash_sim.h"

static uint8_t media[KVSS_TEST_MAX_SECTOR_COUNT * KVSS_TEST_MAX_SECTOR_SIZE];
static struct flash_parameters params;
static uint32_t media_size;

struct flash_sim_stats flash_sim_stats;
struct flash_sim_thresholds flash_sim_thresholds;
bool flash_sim_explicit_erase = true;

int kvss_test_flash_init(uint32_t sector_size, uint32_t sector_count, uint32_t write_block_size,
                         uint8_t erase_value, bool explicit_erase) {
    if ((sector_size == 0U) || (sector_size > KVSS_TEST_MAX_SECTOR_SIZE) || (sector_count < 2U) ||
        (sector_count > KVSS_TEST_MAX_SECTOR_COUNT)) {
        return -EINVAL;
    }

    if ((write_block_size == 0U) || ((write_block_size & (write_block_size - 1U)) != 0U) ||
        (write_block_size > 32U) || ((sector_size % write_block_size) != 0U)) {
        return -EINVAL;
    }

    params.write_block_size = write_block_size;
    params.page_size = sector_size;
    params.erase_value = erase_value;
    params.caps = explicit_erase ? 0U : KVSS_FLASH_CAP_NO_EXPLICIT_ERASE;

    media_size = sector_size * sector_count;
    flash_sim_explicit_erase = explicit_erase;

    kvss_test_flash_reset();
    return 0;
}

void kvss_test_flash_reset(void) {
    memset(media, params.erase_value, media_size);
    memset(&flash_sim_stats, 0, sizeof(flash_sim_stats));
    memset(&flash_sim_thresholds, 0, sizeof(flash_sim_thresholds));
}

static bool range_valid(uint32_t addr, size_t size) {
    return (addr <= media_size) && (size <= media_size - addr);
}

static int sim_read(uint32_t addr, uint8_t *buf, size_t size) {
    if (!buf || !range_valid(addr, size)) {
        return -EINVAL;
    }

    memcpy(buf, media + addr, size);
    return 0;
}

static int sim_write(uint32_t addr, const uint8_t *buf, size_t size) {
    if (!buf || !range_valid(addr, size)) {
        return -EINVAL;
    }

    if (((addr % params.write_block_size) != 0U) || ((size % params.write_block_size) != 0U)) {
        return -EINVAL;
    }

    flash_sim_stats.flash_write_calls += 1U;

    if (flash_sim_explicit_erase) {
        /* NOR flash can only be programmed after an erase. */
        for (size_t i = 0U; i < size; i++) {
            if (media[addr + i] != params.erase_value) {
                return -EIO;
            }
        }
    }

    if (flash_sim_thresholds.max_write_calls != 0U) {
        if (flash_sim_stats.flash_write_calls > flash_sim_thresholds.max_write_calls) {
            return 0;
        }
        if (flash_sim_stats.flash_write_calls == flash_sim_thresholds.max_write_calls) {
            if (flash_sim_thresholds.max_len == 0U) {
                return 0;
            }
            if (size > flash_sim_thresholds.max_len) {
                size = flash_sim_thresholds.max_len;
            }
        }
    }

    if (!flash_sim_explicit_erase) {
        memcpy(media + addr, buf, size);
        return 0;
    }

    for (size_t i = 0U; i < size; i++) {
        if (params.erase_value == 0xffU) {
            media[addr + i] &= buf[i];
        } else {
            media[addr + i] |= buf[i];
        }
    }

    return 0;
}

static int sim_erase(uint32_t offset, size_t size) {
    if (!range_valid(offset, size)) {
        return -EINVAL;
    }

    if (((offset % params.page_size) != 0U) || ((size % params.page_size) != 0U)) {
        return -EINVAL;
    }

    flash_sim_stats.flash_erase_calls += 1U;

    if ((flash_sim_thresholds.max_erase_calls != 0U) &&
        (flash_sim_stats.flash_erase_calls >= flash_sim_thresholds.max_erase_calls)) {
        return 0;
    }

    memset(media + offset, params.erase_value, size);
    return 0;
}

static int sim_lock(uint32_t timeout) {
    (void)timeout;
    return 0;
}

static void sim_unlock(void) {
}

struct flash_parameters *kvss_test_flash_parameters(void) {
    return &params;
}

struct kvss_hal_flash kvss_test_flash_device(void) {
    struct kvss_hal_flash device = {
        .get_parameters = kvss_test_flash_parameters,
        .read = sim_read,
        .write = sim_write,
        .erase = sim_erase,
    };

    return device;
}

struct kvss_hal_mutex kvss_test_mutex(void) {
    struct kvss_hal_mutex mutex = {
        .lock = sim_lock,
        .unlock = sim_unlock,
    };

    return mutex;
}

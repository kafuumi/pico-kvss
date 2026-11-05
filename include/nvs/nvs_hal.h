#if !defined(NVS_HAL_H_)
#define NVS_HAL_H_

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NVS_HAL_TIMEOUT_FOREVER UINT32_MAX

struct nvs_hal_mutex {
    int (*lock)(uint32_t timeout);
    void (*unlock)();
};

struct flash_parameters {
    uint32_t write_block_size;
    uint32_t page_size;
};

struct nvs_hal_flash {
    struct flash_parameters *(*get_parameters)();
    ssize_t (*read)(uint32_t addr, uint8_t *buf, size_t size);
    ssize_t (*write)(uint32_t addr, const uint8_t *buf, size_t size);
    ssize_t (*erase)(uint32_t offset, size_t size);
};

#ifdef __cplusplus
}
#endif

#endif /* NVS_HAL_H_ */
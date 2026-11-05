#if !defined(NVS_HAL_H_)
#define NVS_HAL_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define KVSS_HAL_TIMEOUT_FOREVER UINT32_MAX

/* Deprecated compatibility alias. */
#define NVS_HAL_TIMEOUT_FOREVER KVSS_HAL_TIMEOUT_FOREVER

/* Erase capability reported by kvss_flash_params_get_erase_cap(). */
#define KVSS_FLASH_ERASE_C_EXPLICIT 0x01u

/*
 * Capability bits stored in struct flash_parameters::caps.
 * A zero value describes a regular NOR flash: an explicit erase is required
 * before writing and the erased value can be read back.
 */
#define KVSS_FLASH_CAP_NO_EXPLICIT_ERASE (1u << 0)
#define KVSS_FLASH_CAP_ERASE_VALUE_UNREADABLE (1u << 1)

struct kvss_hal_mutex {
    int (*lock)(uint32_t timeout);
    void (*unlock)();
};

struct flash_parameters {
    uint32_t write_block_size;
    uint32_t page_size;
    uint8_t erase_value;
    /* Combination of KVSS_FLASH_CAP_* bits. */
    uint32_t caps;
};

static inline uint32_t kvss_flash_params_get_erase_cap(const struct flash_parameters *parameters) {
    return (parameters->caps & KVSS_FLASH_CAP_NO_EXPLICIT_ERASE) ? 0u : KVSS_FLASH_ERASE_C_EXPLICIT;
}

static inline bool kvss_flash_params_erase_value_readable(const struct flash_parameters *parameters) {
    return (parameters->caps & KVSS_FLASH_CAP_ERASE_VALUE_UNREADABLE) == 0u;
}

struct kvss_hal_flash {
    struct flash_parameters *(*get_parameters)();
    int (*read)(uint32_t addr, uint8_t *buf, size_t size);
    int (*write)(uint32_t addr, const uint8_t *buf, size_t size);
    int (*erase)(uint32_t offset, size_t size);
};

#ifdef __cplusplus
}
#endif

#endif /* NVS_HAL_H_ */

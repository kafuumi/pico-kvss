#if !defined(ZMS_CRC_H_)
#define ZMS_CRC_H_

#include <stddef.h>
#include <stdint.h>

uint8_t crc8_ccitt(uint8_t val, const void *buf, size_t cnt);

uint32_t crc32_ieee(const uint8_t *data, size_t len);

uint32_t crc32_ieee_update(uint32_t crc, const uint8_t *data, size_t len);

#endif
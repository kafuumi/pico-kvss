#if !defined(UTILS_MICRO_H_)
#define UTILS_MICRO_H_

#define BITS_PER_LONG (__CHAR_BIT__ * __SIZEOF_LONG__)
#define BITS_PER_LONG_LONG (__CHAR_BIT__ * __SIZEOF_LONG_LONG__) /* 64 */
#define GENMASK(h, l) (((~0UL) - (1UL << (l)) + 1) & (~0UL >> (BITS_PER_LONG - 1 - (h))))
#define GENMASK64(h, l) (((~0ULL) - (1ULL << (l)) + 1) & (~0ULL >> (BITS_PER_LONG_LONG - 1 - (h))))
#define LSB_GET(value) ((value) & -(value))
#define FIELD_GET(mask, value) (((value) & (mask)) / LSB_GET(mask))
#define FIELD_PREP(mask, value) (((value) * LSB_GET(mask)) & (mask))

#if !defined(MIN)
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#if !defined(MAX)
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(arr) ((sizeof((arr))) / (sizeof((arr)[0])))
#endif /* ARRAY_SIZE */

#if !defined(KB)
#define KB(value) (size_t)((value) << 10)
#endif

#endif

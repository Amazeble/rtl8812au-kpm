#ifndef RTL8812AU_COMPAT_H
#define RTL8812AU_COMPAT_H

#include <stdint.h>
#include <stddef.h>

#include <kpmalloc.h>

#define RTL8812AU_KPM_OK       0
#define RTL8812AU_KPM_ENOSYS  (-38)
#define RTL8812AU_KPM_EINVAL  (-22)
#define RTL8812AU_KPM_ENODEV  (-19)

/*
 * KPM memory wrappers.
 *
 * These intentionally use KernelPatch's allocator rather than
 * pretending that the normal Linux module allocator is available.
 */
static inline void *rtl_kpm_malloc(size_t size)
{
    return kp_malloc(size);
}

static inline void rtl_kpm_free(void *ptr)
{
    if (ptr)
        kp_free(ptr);
}

/*
 * Driver subsystems that have not yet been ported must fail
 * explicitly rather than returning success.
 */

static inline int rtl_kpm_unimplemented(
    const char *subsystem)
{
    (void)subsystem;
    return RTL8812AU_KPM_ENOSYS;
}

#endif
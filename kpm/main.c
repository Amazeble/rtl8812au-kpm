/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * RTL8812AU KernelPatch Module
 *
 * KPM entry point and lifecycle management.
 */

#include <compiler.h>
#include <kpmodule.h>
#include <common.h>
#include <kputils.h>
#include <linux/printk.h>
#include <linux/string.h>

#include "rtl8812au_kpm.h"

KPM_NAME("rtl8812au");

KPM_VERSION("5.2.20-kpm0");

KPM_LICENSE("GPL v2");

KPM_AUTHOR("Amazeble / KernelPatch port");

KPM_DESCRIPTION(
    "RTL8812AU KernelPatch module port for ARM64"
);

/*
 * KPM initialization.
 *
 * args:
 *     Arguments supplied by the KPM loader.
 *
 * event:
 *     Load/event name.
 *
 * reserved:
 *     Reserved by KernelPatch and currently NULL.
 */
static long rtl8812au_init(
    const char *args,
    const char *event,
    void *reserved
)
{
    int ret;

    (void)reserved;

    pr_info(
        "rtl8812au-kpm: init event=%s args=%s\n",
        event ? event : "(null)",
        args ? args : "(null)"
    );

    pr_info(
        "rtl8812au-kpm: KernelPatch version=%x\n",
        kpver
    );

    ret = rtl8812au_kpm_init();

    if (ret) {
        pr_err(
            "rtl8812au-kpm: initialization failed: %d\n",
            ret
        );

        return ret;
    }

    pr_info(
        "rtl8812au-kpm: initialized\n"
    );

    return 0;
}

/*
 * ctl0 interface.
 *
 * This is intentionally a small diagnostic/control interface.
 * It does NOT claim to provide a Wi-Fi network interface.
 */
static long rtl8812au_ctl0(
    const char *args,
    char *__user out_msg,
    int outlen
)
{
    if (!out_msg || outlen <= 0)
        return RTL8812AU_KPM_EINVAL;

    return rtl8812au_kpm_control(
        args,
        out_msg,
        outlen
    );
}

/*
 * KPM unload callback.
 */
static long rtl8812au_exit(
    void *reserved
)
{
    (void)reserved;

    rtl8812au_kpm_exit();

    pr_info(
        "rtl8812au-kpm: unloaded\n"
    );

    return 0;
}

KPM_INIT(rtl8812au_init);

KPM_CTL0(rtl8812au_ctl0);

KPM_EXIT(rtl8812au_exit);
/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * RTL8812AU KPM runtime.
 *
 * IMPORTANT:
 *
 * This file is deliberately NOT pretending that the ordinary
 * Linux 8812au driver can simply be compiled as a KPM.
 *
 * The original RTL8812AU driver depends heavily on Linux kernel
 * subsystems such as:
 *
 *   - USB
 *   - URBs
 *   - net_device
 *   - cfg80211
 *   - mac80211
 *   - workqueues
 *   - timers
 *   - DMA
 *   - firmware loading
 *   - kernel networking
 *   - Realtek HAL/platform code
 *
 * A functional KPM port has to adapt those interfaces explicitly.
 */

#include <compiler.h>
#include <kpmodule.h>
#include <kputils.h>
#include <kpmalloc.h>
#include <common.h>

#include <linux/printk.h>
#include <linux/string.h>

#include "rtl8812au_kpm.h"

struct rtl8812au_kpm_state rtl8812au_state;

/*
 * KPM-owned initialization.
 */
int rtl8812au_kpm_init(void)
{
    memset(
        &rtl8812au_state,
        0,
        sizeof(rtl8812au_state)
    );

    /*
     * The KPM itself is alive, but the actual RTL8812AU
     * Linux-driver port is not yet installed here.
     */
    rtl8812au_state.initialized = 1;
    rtl8812au_state.driver_port_ready = 0;

    pr_info(
        "rtl8812au-kpm: runtime initialized\n"
    );

    pr_warn(
        "rtl8812au-kpm: RTL8812AU hardware port is not "
        "implemented yet\n"
    );

    return RTL8812AU_KPM_OK;
}

/*
 * KPM-owned cleanup.
 */
void rtl8812au_kpm_exit(void)
{
    if (!rtl8812au_state.initialized)
        return;

    /*
     * Once the actual driver port is implemented, this is where
     * USB registration, network registration, workqueues,
     * timers, firmware state, DMA resources, etc. must be
     * released.
     */

    rtl8812au_state.driver_port_ready = 0;
    rtl8812au_state.initialized = 0;

    pr_info(
        "rtl8812au-kpm: runtime stopped\n"
    );
}

/*
 * Simple ctl0 interface.
 *
 * Examples:
 *
 *   status
 *   version
 *
 * The response is copied to userspace using the official
 * KernelPatch compatibility API.
 */
long rtl8812au_kpm_control(
    const char *args,
    char *__user out_msg,
    int outlen
)
{
    char response[128];
    const char *command;

    if (!out_msg || outlen <= 0)
        return RTL8812AU_KPM_EINVAL;

    memset(
        response,
        0,
        sizeof(response)
    );

    command = args ? args : "";

    if (!strcmp(command, "status")) {

        /*
         * Keep the response small and deterministic.
         */
        snprintf(
            response,
            sizeof(response),
            "initialized=%d driver_port_ready=%d",
            rtl8812au_state.initialized,
            rtl8812au_state.driver_port_ready
        );

    } else if (!strcmp(command, "version")) {

        snprintf(
            response,
            sizeof(response),
            "rtl8812au-kpm 5.2.20-kpm0"
        );

    } else {

        snprintf(
            response,
            sizeof(response),
            "rtl8812au-kpm: unsupported command"
        );
    }

    /*
     * Never copy more than the user's supplied buffer.
     */
    {
        int len = (int)strlen(response) + 1;

        if (len > outlen)
            len = outlen;

        compat_copy_to_user(
            out_msg,
            response,
            len
        );
    }

    return RTL8812AU_KPM_OK;
}
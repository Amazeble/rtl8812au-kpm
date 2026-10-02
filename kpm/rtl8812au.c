/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * RTL8812AU KernelPatch runtime
 *
 * This file provides the KPM-side lifecycle and control runtime.
 *
 * IMPORTANT:
 * This is NOT the RTL8812AU hardware driver yet.
 *
 * The original rtl8812au driver depends on substantial Linux
 * kernel infrastructure:
 *
 *   USB / URB
 *   net_device
 *   cfg80211 / mac80211
 *   workqueues
 *   timers
 *   DMA
 *   firmware loading
 *   networking
 *   Realtek HAL
 *
 * Those interfaces must be ported explicitly before this KPM
 * can operate an RTL8812AU adapter.
 */

#include <compiler.h>
#include <kpmodule.h>
#include <kputils.h>
#include <kpmalloc.h>
#include <common.h>

#include <linux/string.h>
#include <linux/printk.h>

#include "rtl8812au_kpm.h"

struct rtl8812au_kpm_state rtl8812au_state;


/*
 * -------------------------------------------------------------------------
 * Internal helpers
 * -------------------------------------------------------------------------
 */

static const char *rtl8812au_status_string(void)
{
    if (!rtl8812au_state.initialized)
        return "rtl8812au-kpm: stopped";

    if (!rtl8812au_state.driver_port_ready)
        return "rtl8812au-kpm: initialized; driver port incomplete";

    return "rtl8812au-kpm: driver ready";
}


/*
 * -------------------------------------------------------------------------
 * KPM initialization
 * -------------------------------------------------------------------------
 */

int rtl8812au_kpm_init(void)
{
    /*
     * Reset only KPM-owned state.
     */
    memset(
        &rtl8812au_state,
        0,
        sizeof(rtl8812au_state)
    );

    /*
     * Mark the KPM runtime as initialized.
     *
     * driver_port_ready deliberately remains zero.
     *
     * Do NOT claim the RTL8812AU driver is operational until the
     * actual USB/network/HAL port has been implemented.
     */
    rtl8812au_state.initialized = 1;
    rtl8812au_state.driver_port_ready = 0;

    pr_info(
        "rtl8812au-kpm: runtime initialized\n"
    );

    pr_info(
        "rtl8812au-kpm: hardware driver port is not yet installed\n"
    );

    return RTL8812AU_KPM_OK;
}


/*
 * -------------------------------------------------------------------------
 * KPM shutdown
 * -------------------------------------------------------------------------
 */

void rtl8812au_kpm_exit(void)
{
    if (!rtl8812au_state.initialized)
        return;

    /*
     * When the real driver port is implemented, all resources must
     * be released here before returning:
     *
     *   USB registrations
     *   URBs
     *   DMA mappings
     *   workqueues
     *   timers
     *   firmware buffers
     *   network device
     *   cfg80211/mac80211 state
     *   driver-private allocations
     *
     * Nothing is fabricated here.
     */

    rtl8812au_state.driver_port_ready = 0;
    rtl8812au_state.initialized = 0;

    pr_info(
        "rtl8812au-kpm: runtime stopped\n"
    );
}


/*
 * -------------------------------------------------------------------------
 * KPM control interface
 * -------------------------------------------------------------------------
 *
 * Supported commands:
 *
 *   status
 *   version
 *
 * Any other command returns a help message.
 *
 * This interface is deliberately independent of the RTL8812AU
 * hardware until the actual driver port is implemented.
 */

long rtl8812au_kpm_control(
    const char *args,
    char *__user out_msg,
    int outlen
)
{
    const char *response;
    int response_len;
    int copy_len;

    if (!out_msg || outlen <= 0)
        return RTL8812AU_KPM_EINVAL;

    /*
     * status
     */
    if (args && !strcmp(args, "status")) {

        response = rtl8812au_status_string();

    /*
     * version
     */
    } else if (args && !strcmp(args, "version")) {

        response =
            "rtl8812au-kpm: version 5.2.20-kpm0";

    /*
     * help / empty / unknown command
     */
    } else {

        response =
            "rtl8812au-kpm: commands: status, version";
    }

    response_len = (int)strlen(response) + 1;

    /*
     * Do not write beyond the caller's supplied buffer.
     */
    copy_len = response_len;

    if (copy_len > outlen)
        copy_len = outlen;

    /*
     * KernelPatch provides compat_copy_to_user() for the KPM
     * userspace control interface.
     */
    return compat_copy_to_user(
        out_msg,
        response,
        copy_len
    );
}
#include <kpmodule.h>

#include <linux/printk.h>
#include <linux/string.h>

#include "rtl8812au_compat.h"
#include "rtl8812au_kpm.h"

struct rtl8812au_kpm_state rtl8812au_state;

int rtl8812au_driver_init(void)
{
    int ret;

    memset(
        &rtl8812au_state,
        0,
        sizeof(rtl8812au_state)
    );

    ret = rtl8812au_resolve_symbols(
        &rtl8812au_state.symbols
    );

    if (ret) {
        pr_err(
            "rtl8812au-kpm: symbol resolution failed: %d\n",
            ret
        );

        return ret;
    }

    rtl8812au_state.symbols_resolved = 1;

    /*
     * IMPORTANT:
     *
     * This is currently the boundary between the KPM runtime
     * and the actual RTL8812AU driver.
     *
     * USB registration, ieee80211/cfg80211 integration, URBs,
     * DMA, firmware loading, workqueues and the Realtek HAL
     * have NOT been falsely marked as implemented here.
     */

    pr_info(
        "rtl8812au-kpm: compatibility runtime initialized\n"
    );

    rtl8812au_state.initialized = 1;

    return 0;
}

void rtl8812au_driver_exit(void)
{
    if (!rtl8812au_state.initialized)
        return;

    /*
     * Actual RTL8812AU teardown will go here after the
     * corresponding subsystem has been ported.
     */

    rtl8812au_state.initialized = 0;

    pr_info(
        "rtl8812au-kpm: compatibility runtime stopped\n"
    );
}

int rtl8812au_driver_control(
    const char *args,
    char *out,
    int outlen)
{
    const char msg[] =
        "rtl8812au-kpm: runtime loaded; driver port incomplete\n";

    (void)args;

    if (!out || outlen <= 0)
        return RTL8812AU_KPM_EINVAL;

    if (outlen < (int)sizeof(msg))
        return RTL8812AU_KPM_EINVAL;

    memcpy(
        out,
        msg,
        sizeof(msg)
    );

    return 0;
}
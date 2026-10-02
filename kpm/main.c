#include <compiler.h>
#include <kpmodule.h>
#include <kputils.h>

#include <linux/printk.h>
#include <linux/string.h>

#include "rtl8812au_kpm.h"

KPM_NAME("rtl8812au");
KPM_VERSION("5.2.20-kpm0");
KPM_LICENSE("GPL v2");
KPM_AUTHOR("Amazeble / KPM port");
KPM_DESCRIPTION(
    "RTL8812AU KernelPatch port runtime"
);

static long rtl8812au_init(
    const char *args,
    const char *event,
    void *reserved)
{
    int ret;

    (void)reserved;

    pr_info(
        "rtl8812au-kpm: init event=%s args=%s kpver=%x\n",
        event ? event : "(null)",
        args ? args : "(null)",
        kpver
    );

    ret = rtl8812au_driver_init();

    if (ret) {
        pr_err(
            "rtl8812au-kpm: initialization failed: %d\n",
            ret
        );

        return ret;
    }

    return 0;
}

static long rtl8812au_ctl0(
    const char *args,
    char *__user out_msg,
    int outlen)
{
    char response[128];
    int ret;

    memset(
        response,
        0,
        sizeof(response)
    );

    ret = rtl8812au_driver_control(
        args,
        response,
        sizeof(response)
    );

    if (ret)
        return ret;

    ret = compat_copy_to_user(
        out_msg,
        response,
        strlen(response) + 1
    );

    return ret;
}

static long rtl8812au_exit(
    void *reserved)
{
    (void)reserved;

    rtl8812au_driver_exit();

    pr_info(
        "rtl8812au-kpm: unloaded\n"
    );

    return 0;
}

KPM_INIT(rtl8812au_init);
KPM_CTL0(rtl8812au_ctl0);
KPM_EXIT(rtl8812au_exit);
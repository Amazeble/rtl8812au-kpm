#include <kpmodule.h>
#include <kputils.h>

#include <linux/printk.h>
#include <linux/string.h>

#include "rtl8812au_symbols.h"

typedef unsigned long (*kallsyms_lookup_name_t)(
    const char *name
);

static kallsyms_lookup_name_t kp_lookup;

void *rtl8812au_lookup_symbol(
    const char *name)
{
    if (!kp_lookup || !name)
        return NULL;

    return (void *)kp_lookup(name);
}

static void resolve_one(
    void **dst,
    const char *name)
{
    *dst = rtl8812au_lookup_symbol(name);

    if (!*dst)
        pr_warn(
            "rtl8812au-kpm: symbol not found: %s\n",
            name
        );
}

int rtl8812au_resolve_symbols(
    struct rtl8812au_symbols *s)
{
    if (!s)
        return -1;

    memset(s, 0, sizeof(*s));

    kp_lookup =
        (kallsyms_lookup_name_t)
        kallsyms_lookup_name(
            "kallsyms_lookup_name"
        );

    if (!kp_lookup) {
        pr_err(
            "rtl8812au-kpm: kallsyms_lookup_name unavailable\n"
        );

        return -1;
    }

    s->kallsyms_lookup_name =
        (void *)kp_lookup;

    /*
     * These are deliberately resolved individually.
     *
     * A 4.14 Android kernel may not export every symbol,
     * especially depending on vendor configuration.
     */

    resolve_one(
        &s->kmalloc,
        "kmalloc"
    );

    resolve_one(
        &s->kfree,
        "kfree"
    );

    resolve_one(
        &s->vmalloc,
        "vmalloc"
    );

    resolve_one(
        &s->vfree,
        "vfree"
    );

    resolve_one(
        &s->printk,
        "printk"
    );

    resolve_one(
        &s->usb_register_driver,
        "usb_register_driver"
    );

    resolve_one(
        &s->usb_deregister,
        "usb_deregister"
    );

    resolve_one(
        &s->register_netdev,
        "register_netdev"
    );

    resolve_one(
        &s->unregister_netdev,
        "unregister_netdev"
    );

    resolve_one(
        &s->alloc_etherdev,
        "alloc_etherdev"
    );

    resolve_one(
        &s->free_netdev,
        "free_netdev"
    );

    resolve_one(
        &s->schedule_work,
        "schedule_work"
    );

    resolve_one(
        &s->cancel_work_sync,
        "cancel_work_sync"
    );

    resolve_one(
        &s->mod_timer,
        "mod_timer"
    );

    resolve_one(
        &s->del_timer_sync,
        "del_timer_sync"
    );

    return 0;
}
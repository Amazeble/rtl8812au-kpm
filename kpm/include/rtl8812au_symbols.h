#ifndef RTL8812AU_SYMBOLS_H
#define RTL8812AU_SYMBOLS_H

#include <stddef.h>
#include <stdint.h>

struct rtl8812au_symbols {
    void *kallsyms_lookup_name;

    void *kmalloc;
    void *kfree;
    void *vmalloc;
    void *vfree;

    void *printk;

    void *usb_register_driver;
    void *usb_deregister;

    void *register_netdev;
    void *unregister_netdev;

    void *alloc_etherdev;
    void *free_netdev;

    void *schedule_work;
    void *cancel_work_sync;

    void *mod_timer;
    void *del_timer_sync;
};

int rtl8812au_resolve_symbols(
    struct rtl8812au_symbols *s
);

void *rtl8812au_lookup_symbol(
    const char *name
);

#endif
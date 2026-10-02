#ifndef RTL8812AU_KPM_H
#define RTL8812AU_KPM_H

#include <stdint.h>

#include "rtl8812au_symbols.h"

struct rtl8812au_kpm_state {
    int initialized;
    int symbols_resolved;

    struct rtl8812au_symbols symbols;
};

extern struct rtl8812au_kpm_state rtl8812au_state;

int rtl8812au_driver_init(void);

void rtl8812au_driver_exit(void);

int rtl8812au_driver_control(
    const char *args,
    char *out,
    int outlen
);

#endif
#ifndef RTL8812AU_KPM_H
#define RTL8812AU_KPM_H

#include <stdint.h>

#define RTL8812AU_KPM_OK       0
#define RTL8812AU_KPM_EINVAL  (-22)
#define RTL8812AU_KPM_ENOSYS  (-38)

/*
 * This structure intentionally contains only KPM-owned state.
 *
 * It must not pretend to be struct usb_driver, struct net_device,
 * struct ieee80211_hw, etc.
 *
 * Those are Linux kernel subsystem objects and require a real
 * source-level port of the RTL8812AU driver.
 */
struct rtl8812au_kpm_state {
    int initialized;
    int driver_port_ready;
};

extern struct rtl8812au_kpm_state rtl8812au_state;

int rtl8812au_kpm_init(void);
void rtl8812au_kpm_exit(void);

long rtl8812au_kpm_control(
    const char *args,
    char *__user out_msg,
    int outlen
);

#endif
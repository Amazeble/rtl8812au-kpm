# RTL8812AU KPM patches

This directory contains patches applied to:

    Amazeble/rtl8812au
    v5.2.20

## Current status

The KPM runtime is intentionally kept separate from the original
Linux kernel driver.

The following RTL8812AU subsystems still require an actual port:

- Linux module initialization
- Linux module teardown
- USB driver registration
- USB URBs
- USB anchors
- net_device
- cfg80211
- mac80211 integration where applicable
- workqueues
- timers
- spinlocks
- mutexes
- completions
- wait queues
- DMA mapping
- coherent DMA
- skb allocation/free
- firmware loading
- kernel threads
- Realtek HAL
- power-management callbacks

Do NOT add compatibility stubs which return success for these
operations.

A successful build of rtl8812au.kpm does not imply that the USB
adapter works.

## Porting strategy

Port one subsystem at a time.

1. Core memory/string operations
2. USB structures and driver registration
3. URB submission/cancellation
4. Workqueues/timers
5. skb/network integration
6. cfg80211
7. firmware
8. Realtek HAL
9. device initialization
10. suspend/resume

Each patch should compile and have a corresponding runtime test.
# RTL8812AU KernelPatch Module

Experimental port of the Realtek RTL8812AU v5.2.20 driver to
KernelPatch KPM.

## Target

- Android
- ARM64
- Linux 4.14
- APatch / KernelPatch
- RTL8812AU USB adapters

## Important

This project is NOT a conversion of `8812au.ko` into `.kpm`.

A KernelPatch Module is a relocatable ARM64 ELF loaded into kernel
space by KernelPatch.

The original RTL8812AU driver is a conventional Linux kernel driver.
It therefore needs a source-level port.

## Build

Clone KernelPatch:

    git clone https://github.com/bmax121/KernelPatch.git

Clone this repository:

    git clone <this-repository>

Install an ARM GNU bare-metal compiler whose prefix is:

    aarch64-none-elf-

Then:

    export TARGET_COMPILE=/path/to/aarch64-none-elf-

    make -C kpm \
        KP_DIR=/path/to/KernelPatch \
        DRIVER_DIR=/path/to/rtl8812au \
        TARGET_COMPILE="$TARGET_COMPILE"

Output:

    kpm/rtl8812au.kpm

## Kernel compatibility

The KPM is compiled without the Android kernel source tree.

At runtime it resolves kernel functions using KernelPatch's symbol
resolution facilities.

This does NOT guarantee ABI compatibility.

The target Android 4.14 kernel must expose the required symbols and
have compatible internal structures.

## Testing

Do not automatically embed an experimental KPM into boot images.

First load it temporarily through APatch and inspect:

    dmesg | grep rtl8812au

The initial port only verifies the KPM runtime and symbol-resolution
layer.

Actual Wi-Fi operation requires the RTL8812AU subsystems to be
ported.

## License

The RTL8812AU source remains under its original license.

KernelPatch is GPL-2.0.

See the upstream repositories for their respective licenses.
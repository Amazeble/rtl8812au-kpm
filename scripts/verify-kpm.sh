#!/usr/bin/env bash

set -euo pipefail

KPM="${1:?usage: verify-kpm.sh <file.kpm>}"

test -f "$KPM"

echo "== file =="
file "$KPM"

echo
echo "== ELF header =="

readelf -h "$KPM"

echo
echo "== sections =="

readelf -S "$KPM"

echo
echo "== KernelPatch metadata =="

if [ -x "./KernelPatch/tools/kptools" ]; then
    ./KernelPatch/tools/kptools \
        -l \
        -M \
        "$KPM"
fi

echo
echo "== architecture check =="

MACHINE="$(readelf -h "$KPM" | awk -F: '/Machine:/ {print $2}' | xargs)"

case "$MACHINE" in
    AArch64)
        echo "OK: AArch64"
        ;;
    *)
        echo "ERROR: unexpected machine: $MACHINE"
        exit 1
        ;;
esac

echo
echo "KPM validation completed."
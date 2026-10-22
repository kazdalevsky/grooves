#!/usr/bin/env bash
# Cross-compile core/ for Cortex-M7 and print size.
set -e
cd "$(dirname "$0")"
F="-mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard -O2 -std=c++17 -fno-exceptions -fno-rtti -Wall -Wextra"
mkdir -p build-arm
for s in core/*.cpp; do arm-none-eabi-g++ $F -Icore -c "$s" -o "build-arm/$(basename "$s" .cpp).o"; done
arm-none-eabi-size build-arm/*.o

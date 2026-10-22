# Cross-build for Raspberry Pi Zero 2 W / Pi 3 (Cortex-A53, 64-bit Raspberry Pi OS).
# For 32-bit OS use arm-linux-gnueabihf and -mcpu=cortex-a53 -mfpu=neon-fp-armv8.
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_C_COMPILER   aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
set(CMAKE_C_FLAGS_INIT   "-mcpu=cortex-a53")
set(CMAKE_CXX_FLAGS_INIT "-mcpu=cortex-a53")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

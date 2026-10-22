# Groovebox (Raspberry Pi Zero 2 W / Pi 3, Linux)

Платформа: Cortex-A53 x4, 512 МБ (Zero 2) / 1 ГБ (Pi 3), Raspberry Pi OS Lite 64-bit.
Звук: I2S DAC (напр. PCM5102) или USB-аудио через ALSA; у Zero 2 нет аналогового выхода.
Разработка на ПК, кросс-сборка под aarch64 или нативная сборка на самой плате.

## Структура
- core/ — движок (секвенсор, голоса, микшер): чистый C++, без Linux/GPIO/аудио API
- hal/ — интерфейсы: AudioIO, Controls, Display, Storage, Clock
- host/ — ПК: miniaudio, RtMidi, ImGui+SDL2, offline-рендер WAV
- target_pi/ — реализация для Pi (ALSA/miniaudio, GPIO, I2C/SPI дисплей), toolchain-файлы
- tests/ — doctest
- ext/ — submodules (DaisySP как DSP-библиотека, imgui, miniaudio)

## Сборка и тесты
- Host: `cmake -S . -B build -G Ninja && cmake --build build && ctest --test-dir build`
- Sanitizers: `-DGROOVE_SANITIZE=ON`
- Pi (кросс): `cmake -S . -B build-pi -G Ninja -DCMAKE_TOOLCHAIN_FILE=target_pi/toolchain-aarch64.cmake`
  (нужен пакет `g++-aarch64-linux-gnu`)

## Реалтайм-правила (аудио-поток)
Без malloc/new, исключений, мьютексов, printf, файлового ввода-вывода в аудио-callback.
Связь с UI/MIDI — через lock-free очереди. Поток аудио: SCHED_FIFO, mlockall.
Буфер 64-128 фреймов при 48 кГц; при xrun-ах — isolcpus и performance governor.

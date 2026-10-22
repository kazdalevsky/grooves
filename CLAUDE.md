# Groovebox (Daisy Seed, Cortex-M7)

## Структура
- core/ — движок (секвенсор, голоса, микшер), без зависимости от libDaisy
- hal/ — интерфейсы: AudioIO, Controls, Display, Storage, Clock
- host/ — десктоп: miniaudio, RtMidi, ImGui+SDL2
- target_daisy/ — реализация поверх libDaisy, Makefile
- tests/ — doctest + offline-рендер WAV
- ext/ — submodules (libDaisy, DaisySP, imgui, miniaudio)

## Сборка и тесты
- Host: `cmake -S . -B build -G Ninja && cmake --build build && ctest --test-dir build`
- Sanitizers: отдельная конфигурация с `-fsanitize=address,undefined`
- ARM-проверка core/: `-mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard`, затем `arm-none-eabi-size`

## Реалтайм-правила (аудио-callback)
Без malloc/new, исключений, блокировок (mutex), printf и системных вызовов.
Сэмплы и длинные буферы — в SDRAM (64 МБ). Держать запас по CPU: Cortex-M7 480 МГц слабее ПК.

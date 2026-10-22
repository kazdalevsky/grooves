cmake_minimum_required(VERSION 3.20)
project(groovebox CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(GROOVE_SANITIZE "Build with ASan+UBSan" OFF)
if(GROOVE_SANITIZE)
  add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
  add_link_options(-fsanitize=address,undefined)
endif()

add_subdirectory(ext/DaisySP EXCLUDE_FROM_ALL)
target_include_directories(DaisySP PUBLIC ext/DaisySP/Source ext/DaisySP/Source/Utility)

add_library(core STATIC core/voice.cpp)
target_include_directories(core PUBLIC core)
target_link_libraries(core PUBLIC DaisySP)
target_compile_options(core PRIVATE -Wall -Wextra)

enable_testing()
add_executable(tests tests/test_core.cpp)
target_link_libraries(tests PRIVATE core)
add_test(NAME tests COMMAND tests)

add_executable(render host/render_wav.cpp)
target_link_libraries(render PRIVATE core)

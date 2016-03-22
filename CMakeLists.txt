cmake_minimum_required(VERSION 3.5)
project(MI)

# Build the emulation library
add_subdirectory(libmiemu)

# Build the emulator shell wrapper and link with the emulation lib
add_executable(emulator emulator/emulator.cpp)
target_link_libraries(emulator libmiemu)

cmake_minimum_required(VERSION 3.5)
project(MI)

# Set up tests
add_subdirectory(vendor/googletest)
include_directories(${gtest_SOURCE_DIR}/include)
enable_testing()

# Build the emulation library
add_subdirectory(libmiemu)
include_directories(libmiemu)

# Build the emulator shell wrapper and link with the emulation lib
add_executable(emulator emulator/emulator.cpp)
target_link_libraries(emulator libmiemu)

# Build the tests
add_subdirectory(tests)

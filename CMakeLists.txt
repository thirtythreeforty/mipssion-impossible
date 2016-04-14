cmake_minimum_required(VERSION 3.2)
project(MI CXX)

# Set up tests
add_subdirectory(vendor/googletest)
include_directories(${gtest_SOURCE_DIR}/include)
enable_testing()

# Set up termcolor
add_subdirectory(vendor/termcolor)
include_directories(${termcolor_SOURCE_DIR}/include)

# Build the emulation library
add_subdirectory(libmiemu)
include_directories(libmiemu)

# Build the emulator shell wrapper and link with the emulation lib
add_executable(miemu miemu/emulator.cpp)
set_property(TARGET miemu PROPERTY CXX_STANDARD 14)
target_link_libraries(miemu libmiemu)

# Build the tests
add_subdirectory(tests)

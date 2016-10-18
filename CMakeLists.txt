cmake_minimum_required(VERSION 3.2)
project(MI CXX)

if (MSVC)
  # Fix the 1000% nonsense that is Visual Studio.  The build uses
  # conflicting types of libraries by default (!), leading to link
  # errors.  This forces the correct library type.
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
endif()

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
add_executable(miemu
	miemu/emulator.cpp
	miemu/load.cpp
	miemu/REPL.cpp
)
set_property(TARGET miemu PROPERTY CXX_STANDARD 14)
target_link_libraries(miemu libmiemu)

# Build the tests
add_subdirectory(tests)

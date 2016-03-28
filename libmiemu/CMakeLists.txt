project(libmiemu CXX)

# Build the library
add_library(libmiemu
	libmiemu.cpp

	controller.cpp
	datapath.cpp
	program_memory.cpp
)
set_property(TARGET libmiemu PROPERTY CXX_STANDARD 14)

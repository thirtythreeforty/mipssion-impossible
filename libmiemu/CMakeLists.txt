project(miemu)

# Build the library
add_library(libmiemu
	libmiemu.cpp

	controller.cpp
	datapath.cpp
	memory.cpp
)

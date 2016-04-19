project(libmiemu CXX)

# Build the library
add_library(libmiemu
	libmiemu.cpp

	emulator.cpp

	controller.cpp
	datapath.cpp
	program_memory.cpp

	datapath/IF.cpp
	datapath/ID.cpp
	datapath/EX.cpp
	datapath/MEM.cpp
	datapath/WB.cpp
	datapath/register_file.cpp
	datapath/alu.cpp
)
set_property(TARGET libmiemu PROPERTY CXX_STANDARD 14)

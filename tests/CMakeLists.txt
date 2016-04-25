project(mitests CXX)

add_executable(mitests
	test_controller.cpp

	test_memory.cpp
	test_alu.cpp
	test_regfile.cpp

	test_if.cpp
	test_id.cpp
	test_instruction.cpp
	test_ex.cpp
	test_mem.cpp
	test_wb.cpp
	test_hazard.cpp
	test_emulator.cpp
)
set_property(TARGET mitests PROPERTY CXX_STANDARD 14)
target_link_libraries(mitests gtest gtest_main libmiemu)

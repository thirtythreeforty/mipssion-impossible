project(mitests CXX)

add_executable(mitests
	test_memory.cpp
	test_alu.cpp
)
set_property(TARGET mitests PROPERTY CXX_STANDARD 14)
target_link_libraries(mitests gtest gtest_main libmiemu)

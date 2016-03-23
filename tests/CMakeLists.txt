project(mitests CXX)

add_executable(mitests mitests.cpp)
set_property(TARGET mitests PROPERTY CXX_STANDARD 14)
target_link_libraries(mitests gtest gtest_main)

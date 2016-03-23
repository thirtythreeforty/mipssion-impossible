project(mi-tests)

add_executable(mitests mitests.cpp)
target_link_libraries(mitests gtest gtest_main)

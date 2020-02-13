cmake_minimum_required(VERSION 3.1)

set_target_properties(PROPERTIES CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++17 -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++17 -O0")

project(functional_images)
add_subdirectory(src)

enable_testing()
add_subdirectory(test)
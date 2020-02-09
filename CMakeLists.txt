#general project rules
cmake_minimum_required(VERSION 3.1)
project(fimages)

#cpp
set_target_properties(PROPERTIES CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++17 -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++17 -O0")

#variables
set(SRC_PATH "src/")

#sources
add_executable(fimages
        ${SRC_PATH}functional.hpp
        ${SRC_PATH}images.hpp
        ${SRC_PATH}images.cpp
        ${SRC_PATH}coordinate.hpp
        ${SRC_PATH}coordinate.cpp)

#doxygen
find_package(Doxygen)
if (DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
            ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            )
endif (DOXYGEN_FOUND)


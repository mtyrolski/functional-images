#general project rules
cmake_minimum_required(VERSION 3.1)
project(fimages)

#variables
SET(APP_EXE fimages)

#sources
ADD_LIBRARY(fun-image-lib STATIC
        images.cpp
        coordinate.cpp
        color.cpp
        bmp.cpp)

add_executable(${APP_EXE}
        ../example/example.cpp
        )

target_link_libraries(${APP_EXE} fun-image-lib)

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


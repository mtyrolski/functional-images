include_directories (${TEST_SOURCE_DIR}/src)

add_executable(functional_test functional_test.cpp)

target_link_libraries(functional_test
        fun-image-lib
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

add_test(NAME functional_test COMMAND functional_test)
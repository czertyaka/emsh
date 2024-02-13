enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

function(emsh_add_tests)
    set(oneValueArgs TARGET PREFIX)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(EMSH_TEST "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    add_executable("${EMSH_TEST_TARGET}" "${EMSH_TEST_SOURCES}")
    target_link_libraries("${EMSH_TEST_TARGET}" PRIVATE emsh GTest::gtest GTest::gtest_main)
    gtest_discover_tests(
        "${EMSH_TEST_TARGET}"
        TEST_PREFIX "${EMSH_TEST_PREFIX}."
    )
endfunction()

emsh_add_tests(
    TARGET console_input_test
    SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/console/input_test.cpp"
    PREFIX "Console"
)

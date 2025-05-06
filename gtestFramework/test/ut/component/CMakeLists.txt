
# Set configuration names for target
set(COMPONENT_NAME component)
set(OUTPUT_COMPONENT_DIR ${OUTPUT_DIR}/${COMPONENT_NAME})
set(COVERAGE_REPORTS ${OUTPUT_DIR}/${COMPONENT_NAME}_cov)

# Add the files to build, Test files, mock files.
add_executable(${COMPONENT_NAME} 
    <component>_UT.cpp
    ${CMAKE_SOURCE_DIR}/../<ComponentName>.c
    ${CMAKE_CURRENT_SOURCE_DIR}/mocks/<file>_mock.cpp
    ${CMAKE_SOURCE_DIR}/mocks/common/<dependencies>.c
)

# Add the files to build, Test files, mock files.
include_directories(
    # Test Include
    ${CMAKE_SOURCE_DIR}/../<Directory of file under test>
    # mocks includes
    ${CMAKE_SOURCE_DIR}/mocks/common
    ${CMAKE_CURRENT_SOURCE_DIR}/mocks
    # dependencies includes
    ${CMAKE_SOURCE_DIR}/../<dependencies>.c
    ${CMAKE_SOURCE_DIR}/../<dependencies>.c

)

# Set all necesary definitions here
target_compile_definitions(${COMPONENT_NAME} PRIVATE 
    UNIT_TEST
    <preprocessing defines>
)

# Link Test to gtest
target_link_libraries(${COMPONENT_NAME} PRIVATE gmock gtest gtest_main)
include(GoogleTest)

# Add Test module to discovery
gtest_discover_tests(${COMPONENT_NAME})

set_target_properties(${COMPONENT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_COMPONENT_DIR}
)

# Create directory if not exist
file(MAKE_DIRECTORY ${COVERAGE_REPORTS})


add_custom_target(${COMPONENT_NAME}_PostCleanCoverageFiles all
COMMAND rm -rf ${COVERAGE_REPORTS}/*
COMMENT "${Magenta}|| Clean Coverage Reports ${COMPONENT_NAME} ||${ColourReset}"
)

if("${COVERAGE_TOOL}" STREQUAL "GCOV")
  add_custom_target(coverage_gcovr ALL
    COMMAND $<TARGET_FILE:${COMPONENT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/coverage_html
    COMMAND gcovr
            --root ${CMAKE_SOURCE_DIR}/../
            --object-directory ${CMAKE_BINARY_DIR}/../
            --exclude ${CMAKE_SOURCE_DIR}
            --exclude ${CMAKE_BINARY_DIR}
            --html --html-details
            -o ${CMAKE_BINARY_DIR}/coverage_html/index.html
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "${Magenta}|| Generating HTML coverage report with gcovr ||${ColourReset}"
    VERBATIM
)
elseif("${COVERAGE_TOOL}" STREQUAL "LCOV")
  add_custom_target(coverage_lcov ALL
    COMMAND $<TARGET_FILE:${COMPONENT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/coverage_html
    COMMAND lcov --capture
                --directory ${CMAKE_BINARY_DIR}/../
                --output-file ${CMAKE_BINARY_DIR}/coverage.info
                --rc geninfo_unexecuted_blocks=1
                --ignore-errors mismatch
    COMMAND lcov --exclude *test* --exclude /usr/* --remove ${CMAKE_BINARY_DIR}/coverage.info 
                --output-file ${CMAKE_BINARY_DIR}/coverage_filtered.info
    COMMAND genhtml ${CMAKE_BINARY_DIR}/coverage_filtered.info
                    --output-directory ${CMAKE_BINARY_DIR}/coverage_html
    COMMENT "${Magenta}|| Generating HTML coverage report with lcov ||${ColourReset}"

    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    VERBATIM
)
endif()

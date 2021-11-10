cmake_minimum_required(VERSION 3.20)

function(PPtest TARGET_NAME TEST_SOURCES F)
    add_custom_target("${TARGET_NAME}")

    foreach(test_source ${TEST_SOURCES})
        get_filename_component(test "${test_source}" NAME_WE)

        add_executable("${test}" "${test_source}")
        target_include_directories("${test}" PUBLIC "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/..")
        target_link_libraries("${test}" "PPtest")
        add_test("${test}" "${test}")
        add_dependencies("${TARGET_NAME}" "${test}")

        cmake_language(CALL "${F}" "${test}")
    endforeach()
endfunction()

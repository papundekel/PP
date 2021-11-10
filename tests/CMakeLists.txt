cmake_minimum_required(VERSION 3.20)

file(GLOB test_sources "*.cpp")

function("f" TEST)
    target_include_directories("${TEST}" PUBLIC "${CMAKE_CURRENT_LIST_DIR}/..")
    target_link_libraries("${TEST}" "PP")
endfunction()

PPtest("PP-tests" "${test_sources}" "f")
PPstyle("PP-tests")

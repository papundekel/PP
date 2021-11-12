cmake_minimum_required(VERSION 3.20)

file(GLOB test_sources "*.cpp")

function("f" TEST)
    target_include_directories("${TEST}" PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../" "${CMAKE_CURRENT_LIST_DIR}/../vendor/include/")
    target_link_directories("${TEST}" PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../vendor/lib/")
    target_link_libraries("${TEST}" "PP")
    PPstyle("${TEST}")
endfunction()

PPtest("PP-tests" "${test_sources}" "f")

cmake_minimum_required(VERSION 3.20)

file(GLOB test_sources "*.cpp")

function("f" _test)
    PPcmake_target_pedantic_errors("${_test}")
    target_compile_options("${_test}" PUBLIC "-include" "iostream")
    target_include_directories("${_test}" PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../" "${CMAKE_CURRENT_LIST_DIR}/../vendor/include/")
    target_link_directories("${_test}" PUBLIC "${CMAKE_SOURCE_DIR}/vendor/lib/")
    target_link_libraries("${_test}" "PP")
    PPstyle("${_test}")
endfunction()

PPtest("PP-tests" "${test_sources}" "f")

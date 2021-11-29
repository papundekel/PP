cmake_minimum_required(VERSION 3.20)

file(GLOB test_sources "*.cpp")

function("f" _TEST)
    PPcmake_target_pedantic_errors("${_TEST}")
    target_link_libraries("${_TEST}" "PP")
    PPstyle("${_TEST}")
endfunction()

PPtest("PP-tests" "${test_sources}" "f")

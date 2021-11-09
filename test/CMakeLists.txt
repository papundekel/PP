cmake_minimum_required (VERSION 3.8)

file(GLOB test_sources "*.cpp")

list(LENGTH test_sources test_sources_length)

add_executable(PP-test "${test_sources}")
target_compile_features(PP-test PUBLIC cxx_std_20)
target_include_directories(PP-test PUBLIC "${CMAKE_CURRENT_LIST_DIR}/..")
target_compile_definitions(PP-test PUBLIC TEST_COUNT=${test_sources_length})

if(CMAKE_COMPILER_IS_GNUCXX)
    set_target_properties(PP-test PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=5")
endif()

target_link_libraries(PP-test PP)

add_test(NAME PP-test COMMAND PP-test)

PPstyle(PP-test)

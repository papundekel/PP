cmake_minimum_required (VERSION 3.8)

file(GLOB test_sources "*.cpp")

add_executable(PPtest "${test_sources}")
target_compile_features(PPtest PUBLIC cxx_std_20)
target_include_directories(PPtest PUBLIC "${CMAKE_CURRENT_LIST_DIR}/..")

if(CMAKE_COMPILER_IS_GNUCXX)
set_target_properties(PPtest PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=5")
endif()

target_link_libraries(PPtest PP)

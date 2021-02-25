cmake_minimum_required (VERSION 3.8)

project(PP)

add_subdirectory(PP)

target_compile_features(PPlib PUBLIC cxx_std_20)
target_compile_features(PP PUBLIC cxx_std_20)

set_target_properties(PPlib PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=4")
set_target_properties(PP PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=4")

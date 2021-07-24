cmake_minimum_required (VERSION 3.8)

add_library(PP
"string_view.cpp"
"ostream.cpp"
)
target_compile_features(PP PUBLIC cxx_std_20)

if(CMAKE_COMPILER_IS_GNUCXX)
set_target_properties(PP PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=5")
endif()

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" DESTINATION "PPreflection/include" FILES_MATCHING PATTERN "*.hpp")

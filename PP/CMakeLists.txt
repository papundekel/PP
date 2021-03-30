cmake_minimum_required (VERSION 3.8)

add_library(PP
"any_view.cpp"
"string_view.cpp"
)
target_compile_features(PP PUBLIC cxx_std_20)

if(CMAKE_COMPILER_IS_GNUCXX)
set_target_properties(PP PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=5")
endif()

target_precompile_headers(PP PUBLIC
<iostream>
<vector>
<list>
<initializer_list>
<forward_list>
<map>
<type_traits>
<utility>
)

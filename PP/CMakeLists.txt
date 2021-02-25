cmake_minimum_required (VERSION 3.8)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_library(PPlib "any_view.cpp")
add_executable(PP "PP.cpp")
target_link_libraries(PP PPlib)

target_precompile_headers(PPlib PUBLIC
<iostream>
<vector>
<list>
<initializer_list>
<forward_list>
<map>
<type_traits>
<utility>
"any_view.hpp"
)

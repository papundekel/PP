cmake_minimum_required (VERSION 3.8)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_executable(PP "PP.cpp")

target_precompile_headers(PP PUBLIC <iostream> <vector> <list> <initializer_list> <forward_list> <map> <type_traits> <utility>)

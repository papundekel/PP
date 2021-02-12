cmake_minimum_required (VERSION 3.8)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_executable(PP "PP.cpp" "reinterpret_cast.hpp")

target_precompile_headers(PP PUBLIC <iostream> <vector> "any_iterator.hpp")

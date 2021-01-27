cmake_minimum_required (VERSION 3.8)

add_executable(PP "PP.cpp" "tuple_get_element.hpp" "tuple_get_types.hpp" "functional/compose_apply.hpp" "wrap_reference.hpp" "tuple_zip_indices.hpp" "tuple_find_index.hpp" "tuple_view.hpp" "make_in_place_index.hpp" "make_variant_pack.hpp" "variant_visit.hpp")

target_precompile_headers(PP PUBLIC <iostream> <vector>)

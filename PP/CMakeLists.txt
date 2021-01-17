cmake_minimum_required (VERSION 3.8)

add_executable(PP PP.cpp "index_view.hpp" "utility/move.hpp" "singular_tuple.hpp" "concepts/non_array_object.hpp" "concepts/non_void_fundamental.hpp" "concepts/pointer_to_member.hpp" "concepts/enum.hpp" "concepts/user_defined.hpp" "concepts/object.hpp" "concepts/function.hpp" "concepts/function_cvref.hpp" "concepts/atomic/non_array_object.hpp" "fundamental_types.hpp" "concepts/atomic/user_defined.hpp" "concepts/complete_object.hpp" "concepts/referencable.hpp" "concepts/returnable.hpp" "concepts/atomic/pointable.hpp")

#pragma once
#include "concepts/pointable.hpp"
#include "functor.hpp"
#include "remove_reference.hpp"

namespace PP
{
PP_CIA add_pointer = functor(
                         [](concepts::type auto t)
                         {
                             if constexpr (is_pointable(PP_COPY_TYPE(t)))
                                 return type<PP_GT(t)*>;
                             else
                                 return t;
                         }) |
                     remove_reference;
}

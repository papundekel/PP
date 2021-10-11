#pragma once
#include "concepts/pointable.hpp"
#include "functor.hpp"
#include "remove_reference.hpp"

namespace PP::detail
{
namespace functors
{
PP_CIA add_pointer_helper = [](concepts::type auto t)
{
    if constexpr (is_pointable(PP_COPY_TYPE(t)))
        return type<PP_GT(t)*>;
    else
        return t;
};
}
PP_FUNCTOR(add_pointer_helper)
}

namespace PP
{
PP_CIA add_pointer = detail::add_pointer_helper | remove_reference;
}

#pragma once
#include <PP/concepts/pointable.hpp>
#include <PP/remove_reference.hpp>

namespace PP::detail
{
PP_CIA add_pointer_helper = [](concepts::type auto&& t) -> decltype(auto)
{
    if constexpr (is_pointable(PP_CT(t)))
        return type<PP_GT(t)*>;
    else
        return t;
};
}

namespace PP
{
PP_CIA add_pointer = compose(detail::add_pointer_helper, remove_reference);
}

#pragma once
#include <PP/declval_impl.hpp>
#include <PP/get_type.hpp>

namespace PP::concepts
{
template <typename From, typename To>
concept convertible_to = requires
{
    [](To) {}(declval_impl<From>());
};
}

namespace PP
{
PP_CIA is_convertible_to =
    [](concepts::type auto&& from, concepts::type auto&& to)
{
    return concepts::convertible_to<PP_GT(from), PP_GT(to)>;
};
}

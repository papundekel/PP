#pragma once
#include "../declval_impl.hpp"
#include "../functor.hpp"
#include "convertible_to.hpp"

namespace PP::concepts
{
template <typename T, typename U>
concept equatable = requires
{
    {
        declval_impl<T>() == declval_impl<U>()
        } -> convertible_to<bool>;
};
}

namespace PP
{
PP_CIA is_equatable = [](concepts::type auto a, concepts::type auto b)
{
    return concepts::equatable<PP_GT(a), PP_GT(b)>;
};
}

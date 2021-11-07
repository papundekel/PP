#pragma once
#include "declval.hpp"
#include "get_type.hpp"

namespace PP::detail
{
template <typename T>
struct decay_helper : type_t<T>
{
    decay_helper() = default;
    decay_helper(auto&&);
};
template <typename T>
decay_helper(T) -> decay_helper<T>;
}

namespace PP
{
PP_CIA decay = [](concepts::type auto&& t)
{
    return decltype(detail::decay_helper(declval(PP_F(t)))){};
};
}

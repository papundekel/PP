#pragma once
#include "declval.hpp"
#include "get_type.hpp"

namespace PP::detail
{
template <typename T>
struct decay_helper
    : type_t<T>
{
    constexpr decay_helper(auto&&) noexcept
    {}
};
template <typename T>
decay_helper(T) -> decay_helper<T>;
}

namespace PP
{
PP_FUNCTOR(decay, concepts::type auto&& t)
{
    return detail::decay_helper(declval(t));
});
}

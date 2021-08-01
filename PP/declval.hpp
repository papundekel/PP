#pragma once
#include "declval_impl.hpp"
#include "get_type.hpp"

namespace PP
{
auto declval(concepts::type auto&& t) noexcept
    -> decltype(declval_impl<PP_GT(t)>());
}

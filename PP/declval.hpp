#pragma once
#include <PP/declval_impl.hpp>
#include <PP/get_type.hpp>

namespace PP
{
auto declval(concepts::type auto&& t) noexcept
    -> decltype(declval_impl<PP_GT(t)>());
}

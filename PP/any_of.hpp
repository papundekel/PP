#pragma once
#include "view.hpp"
#include <utility>

namespace PP
{
template <view View, typename Predicate>
constexpr bool any_of(View&& v, Predicate&& p)
{
    for (auto&& e : std::forward<View>(v))
        if (std::forward<Predicate>(p)(e))
            return true;
    return false;
}
}

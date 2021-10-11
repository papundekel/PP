#pragma once
#include "../apply_partially_first.hpp"
#include "../get_type.hpp"
#include "for_each.hpp"

namespace PP::detail::functors
{
PP_CIA destroy_helper = [](auto&& x)
{
    using T = PP_GT(~PP_DT(x));
    x.~T();
};
}

namespace PP::view
{
PP_CIA destroy = for_each * detail::functors::destroy_helper;
}

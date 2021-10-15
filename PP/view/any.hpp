#pragma once
#include "find.hpp"

namespace PP::view
{
PP_CIA any = [](auto&& predicate, concepts::view auto&& v)
{
    return find(PP_F(predicate), PP_F(v)) != view::end_(PP_F(v));
};
}

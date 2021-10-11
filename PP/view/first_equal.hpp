#pragma once
#include "../applier.hpp"
#include "../apply_partially_first.hpp"
#include "../negate.hpp"
#include "../operators.hpp"
#include "find.hpp"
#include "zip.hpp"

namespace PP::view
{
namespace functors
{
PP_CIA first_equal_if =
    [](auto&& comparer, concepts::view auto&& a, concepts::view auto&& b)
{
    return find(applier(PP_F(comparer)), zip_pack(PP_F(a), PP_F(b)));
};
PP_CIA first_difference_if =
    [](auto&& comparer, concepts::view auto&& a, concepts::view auto&& b)
{
    return find(negate(applier(PP_F(comparer))), zip_pack(PP_F(a), PP_F(b)));
};
}
PP_FUNCTOR(first_equal_if)
PP_FUNCTOR(first_difference_if)

PP_CIA first_equal = first_equal_if * eql;
PP_CIA first_difference = first_difference_if * eql;
}

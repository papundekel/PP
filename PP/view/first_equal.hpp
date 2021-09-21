#pragma once
#include "../applier.hpp"
#include "../apply_partially_first.hpp"
#include "../negate.hpp"
#include "../operators.hpp"
#include "../view/zip.hpp"
#include "find.hpp"

namespace PP
{
PP_FUNCTOR(view_first_equal_if,
           auto&& comparer,
           concepts::view auto&& a,
           concepts::view auto&& b)
{
    return view_find(applier(PP_F(comparer)), zip_view_pack(PP_F(a), PP_F(b)));
});
PP_FUNCTOR(view_first_difference_if,
           auto&& comparer,
           concepts::view auto&& a,
           concepts::view auto&& b)
{
    return view_find(negate(applier(PP_F(comparer))),
                     zip_view_pack(PP_F(a), PP_F(b)));
});

PP_CIA view_first_equal = view_first_equal_if * eql;
PP_CIA view_first_difference = view_first_difference_if * eql;
}

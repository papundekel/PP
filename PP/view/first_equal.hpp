#pragma once
#include <PP/applier.hpp>
#include <PP/negate.hpp>
#include <PP/operators.hpp>
#include <PP/partial_.hpp>
#include <PP/find.hpp>
#include <PP/view/zip.hpp>

namespace PP::view
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

PP_CIA first_equal = first_equal_if * eql;
PP_CIA first_difference = first_difference_if * eql;
}

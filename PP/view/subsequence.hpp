#pragma once
#include "../containers/array.hpp"
#include "../containers/tuple_std.hpp"
#include "../noop.hpp"
#include "../operators.hpp"
#include "zip_if.hpp"

namespace PP::view
{
enum class subsequence_type
{
    proper,
    equal,
    none,
};

PP_CIA subsequence_if =
    [](auto&& comparer, concepts::view auto&& sub, concepts::view auto&& full)
{
    bool may_be_proper = false;

    auto [sub_end, full_end] = zip_if_pack(
        [&may_be_proper, PP_FWL(comparer)](auto&& sub_element,
                                           auto&& full_element)
        {
            auto cond = comparer(PP_F(sub_element), PP_F(full_element));

            if (!cond)
                may_be_proper = true;

            return tuple::make(cond, array::make(cond, true));
        },
        noop,
        PP_F(sub),
        PP_F(full));

    if (sub_end == end_(PP_F(sub))) {
        if (may_be_proper)
            return subsequence_type::proper;
        else
            return subsequence_type::equal;
    }
    else
        return subsequence_type::none;
};

PP_CIA subsequence = subsequence_if * eql;
}

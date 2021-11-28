#pragma once
#include <PP/containers/array.hpp>
#include <PP/move_assign.hpp>
#include <PP/value_t.hpp>
#include <PP/view/pair.hpp>
#include <PP/zip_if.hpp>

namespace PP::view
{
PP_CIA remove = [](auto&& predicate, concepts::view auto&& v)
{
    return zip_if_pack(
        [&predicate](auto&&, auto&& element)
        {
            auto cond = !PP_F(predicate)(PP_F(element));
            return make_tuple(cond, make_array(cond, true));
        },
        move_assign,
        PP_F(v),
        PP_F(v))[value_0];
};

PP_CIA remove_view = [](auto&& predicate, concepts::view auto&& v)
{
    return pair(begin(PP_F(v)), remove(PP_F(predicate), PP_F(v)));
};
}

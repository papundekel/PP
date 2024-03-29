#pragma once
#include <PP/operators.hpp>
#include <PP/partial_.hpp>
#include <PP/concat.hpp>
#include <PP/tuple/count.hpp>
#include <PP/iterate.hpp>
#include <PP/singular.hpp>
#include <PP/tuple/concept.hpp>
#include <PP/zip_with.hpp>

namespace PP::tuple
{
PP_CIA cartesian_product = [](concepts::tuple auto&& tuples)
{
    if constexpr (type_count(PP_DT(tuples)) != 0 &&
                  all(compose(neq * 0_z, type_count), types(PP_DT(tuples))))
    {
        auto [head_tuples, tail_tuples] = split(PP_F(tuples));

        return concats(zip_with_pack(
            [](auto&& h, auto&& t)
            {
                return map(
                    [&h](auto&& x)
                    {
                        return prepend(PP_F(h), PP_F(x));
                    },
                    PP_F(t));
            },
            PP_F(head_tuples),
            make_iterate_tuple(count_value_t(head_tuples),
                               cartesian_product(move(tail_tuples)))));
    }
    else
        return make_singular_tuple(tuple_empty{};
};

PP_CIA cartesian_product_pack = [](concepts::tuple auto&&... tuples)
{
    return cartesian_product(forward_as_tuple(PP_F(tuples)...));
};
}

#pragma once
#include "../apply_partially_first.hpp"
#include "../forward_wrap.hpp"
#include "../operators.hpp"
#include "all.hpp"
#include "apply.hpp"
#include "concept.hpp"
#include "count.hpp"
#include "empty.hpp"
#include "get.hpp"
#include "make.hpp"
#include "map.hpp"
#include "prepend.hpp"
#include "split.hpp"
#include "types.hpp"

namespace PP::tuple
{
PP_CIA zip = [](concepts::tuple auto&& tuples)
{
    if constexpr (all(compose(neq * 0_z, type_count), types(PP_DT(tuples))))
    {
        auto splits = split + PP_F(tuples);

        return compose(maker, prepend)(get_ * value_0 + move(splits),
                                       zip(get_ * value_1 + move(splits)));
    }
    else
        return tuple_empty{};
};

PP_CIA zip_pack = compose(zip, forward);

PP_CIA zip_with = [](auto&& f, concepts::tuple auto&& tuples)
{
    return apply * forward_wrap(PP_F(f)) + zip(PP_F(tuples));
};

PP_CIA zip_with_pack = [](auto&& f, concepts::tuple auto&&... tuples)
{
    return zip_with(PP_F(f), forward_as_tuple(PP_F(tuples)...));
};
}

constexpr auto operator^(PP::concepts::tuple auto&& a,
                         PP::concepts::tuple auto&& b)
{
    return PP::tuple::zip_pack(PP_F(a), PP_F(b));
}

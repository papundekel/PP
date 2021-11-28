#pragma once
#include <PP/forward_wrap.hpp>
#include <PP/operators.hpp>
#include <PP/partial_.hpp>
#include <PP/tuple/all.hpp>
#include <PP/tuple/apply.hpp>
#include <PP/tuple/concept.hpp>
#include <PP/tuple/count.hpp>
#include <PP/empty.hpp>
#include <PP/tuple/get.hpp>
#include <PP/tuple/make.hpp>
#include <PP/tuple/map.hpp>
#include <PP/tuple/prepend.hpp>
#include <PP/tuple/split.hpp>
#include <PP/tuple/types.hpp>

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

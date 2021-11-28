#pragma once
#include <PP/applier.hpp>
#include <PP/construct_pack.hpp>
#include <PP/get_type.hpp>
#include <PP/tuple/apply.hpp>
#include <PP/tuple/concept.hpp>
#include <PP/tuple/count.hpp>
#include <PP/tuple/map.hpp>
#include <PP/tuple/splits.hpp>
#include <PP/tuple/zip_with.hpp>
#include <PP/value_t.hpp>

namespace PP
{
PP_CIA arg_splitter = [](concepts::type auto&& delimiter_type,
                         concepts::tuple auto&& to_construct_types,
                         concepts::value auto&& i,
                         auto&&... args)
{
    auto splits = tuple::splits(
        [delimiter_type](auto&& arg)
        {
            return value<~PP_DT(arg) == PP_CT(delimiter_type)>;
        },
        forward_as_tuple(PP_F(args)...));

    static_assert(tuple::type_count(PP_DT(to_construct_types)) ==
                      tuple::type_count(PP_DT(splits)),
                  "arg_splitter: bad arg delimiter count");

    return (
        [](concepts::type auto&& to_construct_type, concepts::tuple auto args)
        {
            return [t = move(to_construct_type), as = move(args)]()
            {
                return (construct_pack * t)[move(as)];
            };
        } ++ +(PP_F(to_construct_types) ^ move(splits)))[i]();
};
}

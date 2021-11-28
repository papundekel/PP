#pragma once
#include <PP/containers/tuple.hpp>
#include <PP/forward_wrap.hpp>
#include <PP/get_value.hpp>
#include <PP/type_t.hpp>
#include <PP/empty.hpp>
#include <PP/tuple/fold.hpp>
#include <PP/tuple/make.hpp>
#include <PP/tuple/prepend.hpp>
#include <PP/zip_indices.hpp>

namespace PP::tuple
{
PP_CIA splits = [](auto&& p, concepts::tuple auto&& t)
{
    return foldr(
        [PP_FWL(p)](auto&& element, auto splits)
        {
            if constexpr (PP_GV(p(PP_F(element))))
                return !prepend(tuple_empty{}, move(splits));
            else
                return [PP_FWL(element)](concepts::value auto&& i, auto split)
                {
                    if constexpr (PP_GV(i) == 0)
                        return prepend(element--, move(split));
                    else
                        return move(split);
                } +++zip_indices(move(splits));
        },
        make(tuple_empty{}),
        PP_F(t));
};
}

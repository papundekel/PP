#pragma once
#include <PP/apply_pack.hpp>
#include <PP/containers/tuple.hpp>
#include <PP/get_value.hpp>
#include <PP/partial_.hpp>
#include <PP/utility/move.hpp>

namespace PP
{
PP_CIA partial = [](auto&& f, concepts::value auto&& i, auto&& arg)
{
    return [PP_FL(f), PP_FL(arg)](auto&&... other_args) -> decltype(auto)
    {
        return apply_pack(
            backward(f),
            [&arg, args = tuple::forward(PP_F(other_args)...)](
                concepts::value auto&& current_i) -> decltype(auto)
            {
                constexpr auto CI = PP_CV(current_i);
                constexpr auto I = PP_CV(i);

                if constexpr (CI == I)
                    return backward(arg);
                else if constexpr (CI < I)
                    return move(args)[current_i];
                else
                    return move(args)[current_i - value_1];
            },
            value_sequence_make(PP_SIZEOF___(other_args) + value_1));
    };
};
}

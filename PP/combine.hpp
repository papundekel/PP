#pragma once
#include <PP/forward_wrap.hpp>
#include <PP/macros/CIA.hpp>
#include <PP/macros/functor.hpp>
#include <PP/noop.hpp>
#include <PP/pack/remove_first.hpp>
#include <PP/partial_.hpp>
#include <PP/utility/forward.hpp>

namespace PP
{
PP_CIA combine_constrained = [](auto&& constraint,
                                concepts::value auto&& pack_offset,
                                auto&& c,
                                auto&&... f)
{
    // clang-format off
    return [PP_FL(c), ...PP_FL(f), PP_FL(pack_offset)](auto&&... args) -> decltype(auto)
        requires requires
        {
            PP_F(constraint)(PP_F(args)...);
        }
    // clang-format on
    {
        if constexpr (PP_GV(pack_offset) == -1)
            return backward(c)(backward(f)(PP_F(args)...)...);
        else
            return pack::remove_first(
                pack_offset,
                [c = forward(c), ... f = forward(f), ... PP_FWL(args)](
                    auto&&... pack) -> decltype(auto)
                {
                    return c--(f--(args--...)..., PP_F(pack)...);
                },
                PP_F(args)...);
    };
};

PP_CIA combine = combine_constrained * noop;

PP_CIA combine_no_pack = combine * value<-1>;
}

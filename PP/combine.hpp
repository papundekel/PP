#pragma once
#include "forward_wrap.hpp"
#include "macros/CIA.hpp"
#include "macros/functor.hpp"
#include "noop.hpp"
#include "pack/remove_first.hpp"
#include "partial_.hpp"
#include "utility/forward.hpp"

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
            return unforward(c)(unforward(f)(PP_F(args)...)...);
        else
            return pack::remove_first(
                pack_offset,
                [c = make_fw(c), ... f = make_fw(f), ... PP_FWL(args)](
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

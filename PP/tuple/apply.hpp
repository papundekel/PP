#pragma once
#include "../apply_pack.hpp"
//#include "../apply_partially.hpp"
#include "../functor.hpp"
#include "../functor_concept.hpp"
#include "../utility/forward.hpp"
#include "../value_t.hpp"
#include "concept.hpp"
#include "count.hpp"
#include "get.hpp"
#include "value_sequence_for.hpp"

namespace PP::tuple
{
PP_FUNCTOR(apply, auto&& f, concepts::tuple auto&& t) -> decltype(auto)
{
    return apply_pack(
        PP_F(f),
        // tuple::get(partial_tag, value_1, PP_FW(t)),
        [tt = PP_FW(t)](concepts::value auto&& i) -> decltype(auto)
        {
            return tt-- [PP_F(i)];
        },
        value_sequence_for(PP_F(t)));
});
}

template <typename F>
constexpr decltype(auto) PP::functor<F>::operator[](auto&& t) const&
{
    return tuple::apply(unwrap_functor(*this), PP_F(t));
}

template <typename F>
constexpr decltype(auto) PP::functor<F>::operator[](auto&& t) const&&
{
    return tuple::apply(unwrap_functor(move(*this)), PP_F(t));
}

#pragma once
#include "concepts/copyable.hpp"
#include "declval_impl.hpp"
#include "forward_wrap.hpp"
#include "value_t.hpp"

namespace PP
{
namespace detail
{
template <typename T>
concept functor_member = requires
{
    declval_impl<T>().unwrap_functor();
};
template <typename T>
concept functor_any = detail::functor_member<T> || requires
{
    unwrap_functor_impl(declval_impl<T>());
};
}

constexpr auto&& unwrap_functor(auto&& f)
{
    if constexpr (detail::functor_member<decltype(f)>)
        return unwrap_functor(PP_F(f).unwrap_functor());
    else if constexpr (detail::functor_any<decltype(f)>)
        return unwrap_functor(unwrap_functor_impl(PP_F(f)));
    else
        return PP_F(f);
}

#define PP_UF(x) ::PP::unwrap_functor(PP_F(x))

namespace concepts
{
template <typename T>
concept functor =
    (detail::functor_member<T> || detail::functor_any<T>)&&copyable<
        decltype(unwrap_functor(declval_impl<T>()))>;
}

constexpr decltype(auto) operator<<=(concepts::functor auto&& f, auto&& arg)
{
    return PP_UF(f)(PP_F(arg));
}
}

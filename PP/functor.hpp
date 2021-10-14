#pragma once
#include "concepts/copyable.hpp"
#include "declval_impl.hpp"
#include "macros/functor.hpp"
#include "utility/forward.hpp"

namespace PP::concepts
{
template <typename T>
concept functor = requires
{
    functor_enabler(declval_impl<T>());
};
}

#define PP_FUNCTOR_ENABLER(namespace_name)                                     \
    namespace namespace_name::functors                                         \
    {                                                                          \
    void functor_enabler(auto&&);                                              \
    }

PP_FUNCTOR_ENABLER(PP)
PP_FUNCTOR_ENABLER(PP::detail)
PP_FUNCTOR_ENABLER(PP::tuple)
PP_FUNCTOR_ENABLER(PP::view)

#undef PP_FUNCTOR_ENABLER

constexpr decltype(auto) operator<<=(PP::concepts::functor auto&& f, auto&& arg)
{
    return PP_F(f)(PP_F(arg));
}

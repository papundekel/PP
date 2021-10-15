#pragma once
#include "add_reference.hpp"
#include "apply_transform.hpp"
#include "concepts/reference.hpp"
#include "conditional.hpp"
#include "decompose_template.hpp"

namespace PP
{
namespace detail
{
template <typename T, bool lvalue>
class ref_wrap_impl
{
    using RT =
        apply_transform_t<add_reference * value<lvalue ? ref_qualifier::lvalue
                                                       : ref_qualifier::rvalue>,
                          T>;

    RT ref;

public:
    constexpr ref_wrap_impl(RT ref) noexcept
        : ref((RT)ref)
    {}

    constexpr RT get() const noexcept
    {
        return (RT)ref;
    }
    constexpr operator RT() const noexcept
    {
        return get();
    }

    constexpr decltype(auto) operator()(auto&&... args) const noexcept
    {
        return get()(PP_F(args)...);
    }

    static constexpr bool ref_wrap_impl_tag = true;
};
template <typename T>
ref_wrap_impl(T&) -> ref_wrap_impl<T, true>;
template <typename T>
ref_wrap_impl(T&&) -> ref_wrap_impl<T, false>;
}

template <typename T>
using ref_wrap =
    detail::ref_wrap_impl<PP_GT(!type<T>), is_lvalue_reference(type<T>)>;

template <typename T>
using wrap_ref_t = PP_GT(conditional(value<is_reference(type<T>)>,
                                     type<ref_wrap<T>>,
                                     type<T>));

PP_CIA unwrap_ref = [](auto&& x) -> auto&&
{
    if constexpr (requires
                  {
                      x.ref_wrap_impl_tag;
                  })
        return x.get();
    else
        return PP_F(x);
};

PP_CIA wrap_ref = compose(
    [](auto&& x)
    {
        return ref_wrap<decltype(x)>(PP_F(x));
    },
    unwrap_ref);

#define PP_REF_WRAP(x) ::PP::wrap_ref(PP_F(x))
}

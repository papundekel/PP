#pragma once
#include <PP/add_reference.hpp>
#include <PP/apply_transform.hpp>
#include <PP/concepts/convertible_to.hpp>
#include <PP/construct_pack.hpp>
#include <PP/decompose_template.hpp>
#include <PP/get_type.hpp>
#include <PP/get_value.hpp>
#include <PP/placeholder.hpp>
#include <PP/remove_reference.hpp>

#include <memory>

namespace PP::detail
{
template <typename T, typename U>
concept reference_wrapper_compatible = type<T>
== type<U> || (is_convertible_to(U::base_type, T::base_type) &&
               T::reference_type == U::reference_type);
}

namespace PP
{
template <typename T>
class reference_wrapper
{
    static constexpr auto base_type = !type<T>;
    static constexpr auto reference_type = type<T> + add_rvalue_tag;
    using RT = PP_GT(reference_type);

public:
    PP_GT(base_type) * ptr;

    template <typename U>
    constexpr reference_wrapper(reference_wrapper<U> r) noexcept requires
        detail::reference_wrapper_compatible<reference_wrapper, decltype(r)>
        : ptr(r.ptr)
    {}
    constexpr reference_wrapper(RT ref) noexcept
        : ptr(std::addressof(ref))
    {}

    constexpr auto&& get() const noexcept
    {
        return reference_type(*ptr);
    }
    constexpr operator RT() const noexcept
    {
        return get();
    }

    constexpr decltype(auto) operator()(auto&&... args) const requires requires
    {
        get()(PP_F(args)...);
    }
    {
        return get()(PP_F(args)...);
    }

    template <typename U>
    constexpr auto& operator=(reference_wrapper<U> r) noexcept requires
        detail::reference_wrapper_compatible<reference_wrapper, decltype(r)>
    {
        ptr = r.ptr;
        return *this;
    }
};
template <typename T>
reference_wrapper(T&) -> reference_wrapper<T&>;
template <typename T>
reference_wrapper(T&&) -> reference_wrapper<T&&>;

template <typename T>
using clref_t = reference_wrapper<const T&>;

PP_CIA unref = [](auto&& x) -> decltype(auto)
{
    if constexpr (PP_DT(x)->Template == Template<reference_wrapper>)
        return x.get();
    else
        return PP_F(x);
};

PP_CIA ref = compose(
    [](auto&& x)
    {
        return reference_wrapper(PP_F(x));
    },
    unref);
}

#pragma once
#include "type.hpp"
#include "../utility/bitshift.hpp"

constexpr auto    const_t = bitshift<0>;
constexpr auto volatile_t = bitshift<1>;
constexpr auto     lref_t = bitshift<2>;
constexpr auto     rref_t = bitshift<3>;
constexpr auto      ptr_t = bitshift<4>;

constexpr auto       cv_t = const_t | volatile_t;
constexpr auto      ref_t =  lref_t | rref_t;
constexpr auto    cvref_t =    cv_t | ref_t;

namespace detail::type::basic
{
    template <typename T, auto> constexpr auto __                = t<T>;
    template <typename T,     > constexpr auto __<T,    const_t> = t<const T>;
    template <typename T,     > constexpr auto __<T, volatile_t> = t<volatile T>;
    template <typename T,     > constexpr auto __<T,     lref_t> = t<T&>;
    template <typename T,     > constexpr auto __<T,     rref_t> = t<T&&>;
    template <typename T,     > constexpr auto __<T,      ptr_t> = t<T*>;

    template <auto mask> constexpr auto _ = []<typename T>(type<T>) { return _<T, mask>; };
}

template <auto mask>
using maker = decltype(detail::type::basic::_<mask>);

template <template <auto> typename F, auto mask>
constexpr auto helper = [](auto x)
{
    if constexpr (mask != 0)
    {
        int i = 0;
        while (mask & bitshift<i> == 0) ++i;
        return helper<F, mask ^ bitshit<i>>(F<bitshit<i>>{}(x));
    }
    else
        return x;
};

template <auto mask>
constexpr auto strip = helper<stripper, mask>;

template <auto mask>
constexpr auto make = helper<maker, mask>;

template <auto mask>
constexpr auto is = negation(transform_same(strip<mask>));
#pragma once
#include <PP/get_type.hpp>
#include <PP/get_value.hpp>

namespace PP
{
template <typename T, auto V>
class decompose_pair
{
public:
    constexpr auto tuple_count() const noexcept
    {
        return value_2;
    }
    constexpr auto element(concepts::value auto&& i) const noexcept
    {
        if constexpr (PP_GV(i) == 0)
            return type<type_t<T>>;
        else
            return type<value_t<V>>;
    }
    constexpr auto operator[](concepts::value auto&& i) const noexcept
    {
        if constexpr (PP_GV(i) == 0)
            return type<T>;
        else
            return value<V>;
    }
    template <size_t I>
    constexpr auto get() const noexcept
    {
        return (*this)[value<I>];
    }
};

PP_CIA make_decompose_pair =
    [](concepts::type auto&& t, concepts::value auto&& v)
{
    return decompose_pair<PP_GT(t), PP_GV(v)>{};
};
}

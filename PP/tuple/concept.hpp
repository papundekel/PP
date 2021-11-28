#pragma once
#include <PP/declval.hpp>
#include <PP/get_type.hpp>
#include <PP/macros/simple_concept.hpp>
#include <PP/value_t.hpp>
#include <PP/tuple/count.hpp>
#include <PP/tuple/element.hpp>
#include <PP/tuple/get.hpp>
#include <PP/tuple/value_sequence_for.hpp>

namespace PP::detail
{
template <typename T, auto I>
concept tuple_access = requires
{
    ::PP::declval_impl<T>()[::PP::value<I>];
    ::PP::tuple::element(::PP::value<I>, ::PP::declval_impl<T>());
};
template <typename T, auto... I>
concept tuple_accesses = (tuple_access<T, I> && ...);

template <auto... I>
constexpr auto is_tuple_helper(concepts::type auto&& t,
                               value_sequence<I...>) noexcept
{
    return tuple_accesses<PP_GT(t), I...>;
}
}

namespace PP::concepts
{
template <typename T>
concept tuple = requires
{
    ::PP::tuple::count_value_t(::PP::declval_impl<T>());
}
&&PP::detail::is_tuple_helper(PP::type<T>,
                              tuple::type_value_sequence_for(PP::type<T>));
}

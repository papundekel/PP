#pragma once
#include "arrow_operator_wrapper.hpp"
#include "compose.hpp"
#include "containers/type_tuple.hpp"
#include "remove_cvref.hpp"
#include "template_t.hpp"
#include "type_t.hpp"

template <typename T>
constexpr auto PP::type_t<T>::operator->() const noexcept
{
    return make_arrow_operator_wrapper(
        [this]()
        {
            return **this;
        });
}

namespace PP::detail
{
template <template <typename...> typename T, typename... Types>
struct decompose_pair
{
    template_t<T> Template;
    type_tuple_t<Types...> types;
};

template <typename T>
struct decompose_dummy
{};
}

namespace PP
{
PP_CIA decompose = compose(
    overloaded(
        []<template <typename...> typename T, typename... Types>(
            type_t<T<Types...>>)
        {
            return detail::decompose_pair(Template<T>, type_tuple<Types...>);
        },
        [](auto&&)
        {
            return detail::decompose_pair(Template<detail::decompose_dummy>,
                                          type_tuple<>);
        }),
    remove_cvref);

PP_CIA decompose_template = compose(
    [](auto p)
    {
        return p.Template;
    },
    decompose);
PP_CIA decompose_types = compose(
    [](auto p)
    {
        return p.types;
    },
    decompose);
}

constexpr auto operator*(PP::concepts::type auto t) noexcept
{
    return PP::decompose(t);
}

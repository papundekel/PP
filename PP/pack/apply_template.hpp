#pragma once
#include <PP/get_type.hpp>
#include <PP/macros/functor.hpp>
#include <PP/template_t.hpp>
#include <PP/type_t.hpp>

namespace PP::pack
{
PP_CIA apply_template =
    []<template <typename...> typename Template>(template_t<Template>,
                                                 concepts::type auto&&... types)
{
    return type<Template<PP_GT(types)...>>;
};
}

template <template <typename...> typename Template>
constexpr auto PP::template_t<Template>::operator()(
    auto&&... types) const noexcept
{
    return PP::pack::apply_template(*this, types...);
}

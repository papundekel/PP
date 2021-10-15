#pragma once
#include "get_type.hpp"
#include "macros/functor.hpp"
#include "template_t.hpp"
#include "type_t.hpp"

namespace PP
{
PP_CIA apply_template_pack =
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
    return apply_template_pack(*this, types...);
}

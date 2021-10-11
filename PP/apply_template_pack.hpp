#pragma once
#include "functor.hpp"
#include "get_type.hpp"
#include "get_value.hpp"
#include "template_t.hpp"
#include "type_t.hpp"

namespace PP
{
namespace functors
{
PP_CIA apply_template_pack =
    []<template <typename...> typename Template>(template_t<Template>,
                                                 concepts::type auto... types)
{
    return type<Template<PP_GT(types)...>>;
};
}
PP_FUNCTOR(apply_template_pack)
}

template <template <typename...> typename Template>
constexpr auto PP::template_t<Template>::operator()(
    auto... types) const noexcept
{
    return apply_template_pack(*this, types...);
}

#pragma once
#include "template_tuple.hpp"
#include <tuple>

namespace std
{
template <template <typename...> typename... Templates>
struct tuple_size<PP::template_tuple<Templates...>>
    : public integral_constant<size_t, sizeof...(Templates)>
{};
template <size_t I, template <typename...> typename... Templates>
struct tuple_element<I, PP::template_tuple<Templates...>>
    : public PP::type_t<decltype(PP::template_tuple<Templates...>{}[value<I>])>
{};
}

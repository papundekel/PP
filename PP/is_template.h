#pragma once
#include "value_t.h"

template <template <typename...> typename, typename>
struct is_template : value_t<false> {};

template <template <typename...> typename Template, typename... Pars>
struct is_template<Template, Template<Pars...>> : value_t<true> {};

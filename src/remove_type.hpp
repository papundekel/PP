#pragma once
#include "type.hpp"

namespace dremove_type
{
    template <template <typename> typename F, typename T>
    struct x : type<T> {};
    template <template <typename> typename F, typename T>
    struct x<F, F<T>> : type<T> {};
}

template <template <typename> typename F, typename T>
using remove_type = dremove_type::x<F, T>::t;
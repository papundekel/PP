#pragma once
#include "type_t.hpp"

namespace dremove_type
{
    template <template <typename> typename make>
    struct x
    {
        template <typename T>
        struct y : type_t<T> {};
        template <typename T>
        struct y<make<T>> : type_t<T> {};
    };
}

template <template <typename> typename make, typename T>
using remove_type = dremove_type::x<make>::template y<T>::t;
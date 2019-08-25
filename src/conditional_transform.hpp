#pragma once
#include "type_t.hpp"

namespace detail
{
    template <bool test, template <typename> typename Transform, typename T>
    struct conditional_transform : type_t<Transform<T>> {};
    template <template <typename> typename Transform, typename T>
    struct conditional_transform<false, Transform, T> : type_t<T> {};
}
template <bool test, template <typename> typename Transform, typename T>
using conditional_transform = detail::conditional_transform<test, Transform, T>::t;
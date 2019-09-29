#pragma once
#include "type.hpp"

namespace dconditional_transform
{
    template <bool test, template <typename> typename Transform, typename T>
    constexpr auto x()
    {
        if constexpr (test) return type<Transform<T>>{};
        else				return type<T>{};
    }
}
template <bool test, template <typename> typename Transform, typename T>
using conditional_transform = decl_type<dconditional_transform::x<test, Transform, T>>;
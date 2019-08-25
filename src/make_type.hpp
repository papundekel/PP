#pragma once
#include "value_t.hpp"
#include "keep_cv.hpp"
#include "pack.hpp"
#include "is_type.hpp"

namespace detail::make_type
{
    template <typename T>
    struct a
    {
        template <typename U>
        using b = value_t<sizeof(T) <= sizeof(U)>;
    };

    template <typename P>
    requires is<pack>::type<P>::v
    struct c
    {
        template <typename T>
        using d = P::template get<P::template first_n<P::count - 1>::template find<a<T>::template b>>;
    };
}

template <typename P, typename T>
using make_type = keep_cv<T, detail::make_type::c<P>::template d>;
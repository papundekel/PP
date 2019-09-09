#pragma once
#include "val.hpp"
#include "keep_cv.hpp"
#include "pack.hpp"
#include "is_type.hpp"

namespace dmake_type
{
    template <typename T>
    struct a
    {
        template <typename U>
        using b = val<sizeof(T) <= sizeof(U)>;
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
using make_type = keep_cv<T, dmake_type::c<P>::template d>;
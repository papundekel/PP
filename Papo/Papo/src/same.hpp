#pragma once

namespace detail
{
    template <typename T, typename U> constexpr bool same	    = false;
    template <typename T>			  constexpr bool same<T, T> =  true;
}


template <typename T, typename U>
concept same = detail::same<T, U>;
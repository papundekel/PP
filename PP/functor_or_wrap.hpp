#pragma once
#include "forward_wrap.hpp"
#include "functor.hpp"

namespace PP::concepts
{
template <typename T>
concept forward_wrap = requires
{
    []<typename U>(const forward_wrap<U>&)
    {
    }(declval_impl<T>());
};

template <typename T>
concept functor_or_wrap = functor<T> || forward_wrap<T>;
}

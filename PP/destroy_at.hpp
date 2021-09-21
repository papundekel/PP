#pragma once
#include <memory>

#include "concepts/array.hpp"
#include "functor.hpp"
#include "get_type.hpp"

namespace PP
{
namespace detail
{
template <typename T>
constexpr void destroy_at_impl(T* p)
{
    if constexpr (concepts::array<T>)
    {
        for (auto& x : *p)
            destroy_at_impl(std::addressof(x));
    }
    else
        p->~T();
}
}

PP_FUNCTOR(destroy_at, auto* p)
{
    detail::destroy_at_impl(p);
});
}

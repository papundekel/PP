#pragma once
#include <PP/concepts/array.hpp>
#include <PP/get_type.hpp>

#include <memory>

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

PP_CIA destroy_at = [](auto* p)
{
    detail::destroy_at_impl(p);
};
}

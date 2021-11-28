#pragma once
#include <PP/declval_impl.hpp>
#include <PP/type_t.hpp>

namespace PP::detail
{
template <typename T>
type_t<T> remove_reference_impl_helper(T&);
template <typename T>
type_t<T> remove_reference_impl_helper(T&&);
}

namespace PP
{
template <typename T>
using remove_reference_impl =
    decltype(detail::remove_reference_impl_helper(declval_impl<T>()))::type;
}

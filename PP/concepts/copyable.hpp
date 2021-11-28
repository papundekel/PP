#pragma once
#include <PP/declval_impl.hpp>
#include <PP/remove_reference_impl.hpp>

namespace PP
{
namespace concepts
{

template <typename T>
concept copyable = requires
{
    [](auto) {}(declval_impl<T>());
};
}
}

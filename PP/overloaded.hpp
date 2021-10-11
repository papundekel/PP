#pragma once
#include "functor.hpp"

namespace PP
{
namespace functors
{
template <typename... Ts>
struct overloaded
    : public Ts...
{
    using Ts::operator()...;
};
template <typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;
}
using functors::overloaded;
}

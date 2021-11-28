#pragma once
#include <PP/fundamental_types.hpp>

namespace PP
{
namespace concepts
{
template <typename T>
concept floating_point = float_type<T> || double_type<T> || long_double<T>;
}

PP_CONCEPT_FUNCTOR1(floating_point);
}

#pragma once
#include "reference.hpp"
#include "scalar.hpp"
#include "with_trivial_destructor.hpp"

namespace PP
{
namespace concepts
{
template <typename T>
concept trivially_destructible =
	reference<T> || scalar<T> || with_trivial_destructor<T>;
}

PP_CONCEPT_FUNCTOR1(trivially_destructible);
}

#pragma once
#include <PP/get_type.hpp>

namespace PP
{
template <auto f, typename T>
using apply_transform_t = PP_GT(f(type<T>));

#define PP_APPLY_TRANSFORM(f, t) ::PP::apply_transform_t<f, PP_GT(t)>
}

#pragma once
#include "conditional_transform.hpp"
#include "const_type.hpp"
#include "volatile_type.hpp"
template <typename T, template <typename> typename Transform>
using keep_cv =
conditional_transform<   const_type<T>::v, make_const,
conditional_transform<volatile_type<T>::v, make_volatile,
Transform<T>>>;
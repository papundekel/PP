#pragma once
#include "same.hpp"
template <typename Type, template <typename> typename MakeTrait>
using has_projective_trait = same<Type, MakeTrait<Type>>;
#pragma once
#include "same_except_cv.hpp"

namespace PP::concepts
{
template <typename T>
concept non_void = different_except_cv<T, void>;
}

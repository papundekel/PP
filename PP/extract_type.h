#pragma once
#include "type_t.h"
#include "get_type.h"

template <typename T>
using extract_type = type_t<get_type<T>>;

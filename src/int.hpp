#pragma once
#include <cstddef>
#include "fundamental_integers_signed.hpp"
#include "make_integer_unsigned.hpp"
#include "type_get.hpp"
#include "type_size.hpp"
using diff_t = decl_type<get(fundamental_integers_signed, [](auto x){ return size(x) == sizeof(void*); })>;
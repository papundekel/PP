#pragma once
#include "compose.hpp"
#include "decl_type.hpp"
#include "get_type.hpp"

namespace PP
{
PP_CIA to_type_t = compose(get_type, decl_type_copy);
}

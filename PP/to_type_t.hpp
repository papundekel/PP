#pragma once
#include <PP/compose.hpp>
#include <PP/decl_type.hpp>
#include <PP/get_type.hpp>

namespace PP
{
PP_CIA to_type_t = compose(get_type, decl_type_copy);
}

#pragma once
#include "../applier.hpp"
#include "../compose.hpp"
#include "../move_assign.hpp"
#include "../operators.hpp"
#include "../partial_.hpp"
#include "../utility/move.hpp"
#include "for_each.hpp"
#include "zip.hpp"

namespace PP::view
{
PP_CIA move = compose(for_each * move_assign++, zip_pack);
}

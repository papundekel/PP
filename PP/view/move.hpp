#pragma once
#include "../applier.hpp"
#include "../apply_partially_first.hpp"
#include "../compose.hpp"
#include "../move_assign.hpp"
#include "../operators.hpp"
#include "../utility/move.hpp"
#include "for_each.hpp"
#include "zip.hpp"

namespace PP
{
PP_CIA view_move = view_for_each * *move_assign | zip_view_pack;
}
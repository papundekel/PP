#pragma once
#include "../applier.hpp"
#include "../apply_partially_first.hpp"
#include "../compose.hpp"
#include "../operators.hpp"
#include "for_each.hpp"
#include "zip.hpp"

namespace PP::view
{
PP_CIA copy = for_each * *asg | zip_view_pack;
}

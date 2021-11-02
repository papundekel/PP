#pragma once
#include "../applier.hpp"
#include "../compose.hpp"
#include "../operators.hpp"
#include "../partial_.hpp"
#include "for_each.hpp"
#include "zip.hpp"

namespace PP::view
{
PP_CIA copy = compose(for_each * asg++, zip_pack);
}

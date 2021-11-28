#pragma once
#include <PP/applier.hpp>
#include <PP/compose.hpp>
#include <PP/move_assign.hpp>
#include <PP/operators.hpp>
#include <PP/partial_.hpp>
#include <PP/utility/move.hpp>
#include <PP/view/for_each.hpp>
#include <PP/view/zip.hpp>

namespace PP::view
{
PP_CIA move = compose(for_each * move_assign++, zip_pack);
}

#pragma once
#include <PP/applier.hpp>
#include <PP/compose.hpp>
#include <PP/operators.hpp>
#include <PP/partial_.hpp>
#include <PP/view/for_each.hpp>
#include <PP/view/zip.hpp>

namespace PP::view
{
PP_CIA copy = compose(for_each * asg++, zip_pack);
}

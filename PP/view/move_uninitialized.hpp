#pragma once
#include <memory>

#include "../applier.hpp"
#include "../apply_partially_first.hpp"
#include "../construct_at_pack.hpp"
#include "../operators.hpp"
#include "../utility/move.hpp"
#include "for_each.hpp"
#include "zip.hpp"

namespace PP::detail::functors
{
PP_CIA move_uninitialized_helper = [](auto&& to, auto&& from)
{
    construct_at_pack(std::addressof(to), PP::move(from));
};
}

namespace PP::view
{
PP_CIA move_uninitialized =
    for_each * detail::functors::move_uninitialized_helper++ | zip_pack;
}

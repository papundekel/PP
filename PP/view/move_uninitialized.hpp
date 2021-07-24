#pragma once
#include <memory>

#include "applier.hpp"
#include "apply_partially_first.hpp"
#include "construct_at_pack.hpp"
#include "operators.hpp"
#include "utility/move.hpp"
#include "view/for_each.hpp"
#include "view/zip.hpp"

namespace PP
{
constexpr inline auto view_move_uninitialized =
    view_for_each * *functor(
                        [](auto&& to, auto&& from)
                        {
	                        construct_at_pack(std::addressof(to), move(from));
                        }) |
    zip_view_pack;
}

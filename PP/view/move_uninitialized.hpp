#pragma once
#include "../applier.hpp"
#include "../construct_at_pack.hpp"
#include "../operators.hpp"
#include "../partial_.hpp"
#include "../utility/move.hpp"
#include "for_each.hpp"
#include "zip.hpp"

#include <memory>

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
    compose(for_each * detail::functors::move_uninitialized_helper++, zip_pack);
}

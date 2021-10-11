#pragma once
#include <memory>

#include "../applier.hpp"
#include "../apply_partially_first.hpp"
#include "../construct_at_pack.hpp"
#include "../operators.hpp"
#include "../utility/forward.hpp"
#include "for_each.hpp"
#include "zip.hpp"

namespace PP::detail::functors
{
PP_CIA copy_uninitialized_helper = [](auto&& to, auto&& from)
{
    construct_at_pack(std::addressof(to), PP_F(from));
};
}

namespace PP::view
{
PP_CIA copy_uninitialized =
    for_each * detail::functors::copy_uninitialized_helper++ | zip_pack;
}

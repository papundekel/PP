#pragma once
#include <PP/applier.hpp>
#include <PP/construct_at_pack.hpp>
#include <PP/operators.hpp>
#include <PP/partial_.hpp>
#include <PP/utility/move.hpp>
#include <PP/view/for_each.hpp>
#include <PP/view/zip.hpp>

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

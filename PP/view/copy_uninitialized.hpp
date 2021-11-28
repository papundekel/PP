#pragma once
#include <PP/applier.hpp>
#include <PP/construct_at_pack.hpp>
#include <PP/operators.hpp>
#include <PP/partial_.hpp>
#include <PP/utility/forward.hpp>
#include <PP/view/for_each.hpp>
#include <PP/view/zip.hpp>

#include <memory>

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
    compose(for_each * detail::functors::copy_uninitialized_helper++, zip_pack);
}

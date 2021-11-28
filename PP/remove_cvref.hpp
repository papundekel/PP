#pragma once
#include <PP/compose.hpp>
#include <PP/remove_cv.hpp>
#include <PP/remove_reference.hpp>

namespace PP
{
PP_CIA remove_cvref = compose(remove_cv, remove_reference);
}

constexpr auto operator~(PP::concepts::type auto&& t) noexcept
{
    return PP::remove_cvref(t);
}

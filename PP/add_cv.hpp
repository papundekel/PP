#pragma once
#include "add_const.hpp"
#include "add_volatile.hpp"
#include "cv_qualifier.hpp"
#include "get_value.hpp"

namespace PP
{
PP_CIA add_cv = [](concepts::value auto&& cv, concepts::type auto&& t)
{
    constexpr auto CV = *PP_CV(cv);

    if constexpr (CV == cv_qualifier::none)
        return t;
    else if constexpr (CV == cv_qualifier::Const)
        return add_const(t);
    else if constexpr (CV == cv_qualifier::Volatile)
        return add_volatile(t);
    else
        return add_const(add_volatile(t));
};

///
/// @brief Empty tag type used for adding a cv qualifier.
///
/// @tparam cv The cv qualifier to add.
///
template <cv_qualifier cv>
struct add_cv_tag_t
    : public value_t<cv>
{};

constexpr inline add_cv_tag_t<cv_qualifier::Const> add_const_tag = {};
constexpr inline add_cv_tag_t<cv_qualifier::Volatile> add_volatile_tag = {};
constexpr inline add_cv_tag_t<cv_qualifier::const_volatile>
    add_const_volatile_tag = {};

}

template <PP::cv_qualifier cv>
constexpr auto operator+(PP::concepts::type auto&& t,
                         PP::add_cv_tag_t<cv> tag) noexcept
{
    return PP::add_cv(tag, PP_F(t));
}

#pragma once
#include "concepts/atomic/referencable.hpp"
#include "get_type.hpp"
#include "get_value.hpp"
#include "ref_qualifier.hpp"

namespace PP
{
PP_CIA add_reference = [](concepts::value auto&& ref, concepts::type auto&& t)
{
    using T = PP_GT(t);

    constexpr auto REF = *PP_CV(ref);

    if constexpr (is_referencable(type<T>)) {
        if constexpr (REF == ref_qualifier::lvalue)
            return type<T&>;
        else if constexpr (REF == ref_qualifier::rvalue)
            return type<T&&>;
        else
            return t;
    }
    else
        return t;
};

///
/// @brief Empty tag type used for adding a ref qualifier.
///
/// @tparam ref The ref qualifier to add.
///
template <ref_qualifier ref>
struct add_reference_tag_t : public value_t<ref> {};

constexpr inline add_reference_tag_t<ref_qualifier::lvalue> add_lvalue_tag{};
constexpr inline add_reference_tag_t<ref_qualifier::rvalue> add_rvalue_tag{};
}

template <PP::ref_qualifier ref>
constexpr auto operator+(PP::concepts::type auto&& t,
                         PP::add_reference_tag_t<ref> tag) noexcept
{
    return PP::add_reference(tag, PP_F(t));
}

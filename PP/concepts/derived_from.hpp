#pragma once
#include <PP/get_type.hpp>
#include <PP/class.hpp>
#include <PP/concepts/convertible_to.hpp>

namespace PP
{
namespace concepts
{
template <typename D, typename B>
concept derived_from = class_type<D> && class_type<B> &&
    convertible_to<const volatile D*, const volatile B*>;
}

PP_CIA is_derived_from = [](concepts::type auto&& d, concepts::type auto&& b)
{
    return concepts::derived_from<PP_GT(d), PP_GT(b)>;
};
}

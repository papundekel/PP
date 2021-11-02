#pragma once
#include "../conditional.hpp"
#include "../declval.hpp"
#include "../get_type.hpp"
#include "../partial.hpp"
#include "../tuple/apply.hpp"
#include "../value_t.hpp"

namespace PP::concepts
{
template <typename T, typename... Args>
concept constructible = requires
{
    T(declval_impl<Args>()...);
};
template <typename T, typename... Args>
concept constructible_noexcept = requires
{
    {
        T(declval_impl<Args>()...)
    }
    noexcept;
};
}

namespace PP::detail
{
PP_CIA is_constructible_pack_impl = [](concepts::value auto&& Noexcept,
                                       concepts::type auto&& t,
                                       concepts::type auto... arg_types)
{
    if constexpr (PP_GV(Noexcept))
        return concepts::constructible_noexcept<PP_GT(t), PP_GT(arg_types)...>;
    else
        return concepts::constructible<PP_GT(t), PP_GT(arg_types)...>;
};

PP_CIA is_constructible_impl = [](concepts::value auto&& Noexcept,
                                  concepts::type auto&& t,
                                  concepts::tuple auto arg_tuple)
{
    return (is_constructible_pack_impl * Noexcept * t)[arg_tuple];
};
}

namespace PP
{
PP_CIA is_constructible_pack = detail::is_constructible_pack_impl * value_false;
PP_CIA is_constructible_noexcept_pack =
    detail::is_constructible_pack_impl * value_true;

PP_CIA is_constructible = detail::is_constructible_impl * value_false;
PP_CIA is_constructible_noexcept = detail::is_constructible_impl * value_true;
}

#pragma once
#include <PP/decl_type.hpp>
#include <PP/declval_impl.hpp>
#include <PP/get_type.hpp>
#include <PP/overloaded.hpp>
#include <PP/remove_reference_impl.hpp>
#include <PP/value_t.hpp>

namespace PP::detail
{
template <typename T>
concept has_value_f = requires
{
    remove_reference_impl<T>::value_f();
};
template <typename T>
concept has_value = !has_value_f<T> && requires
{
    remove_reference_impl<T>::value;
};
}

namespace PP::concepts
{
template <typename T>
concept value = detail::has_value_f<T> || detail::has_value<T>;
}

namespace PP
{
PP_CIA get_type_value = overloaded(
    [](auto&& t) -> decltype(auto) requires detail::has_value_f<PP_GT(t)> {
        return remove_reference_impl<PP_GT(t)>::value_f();
    },
    [](auto&& t) -> decltype(auto) requires detail::has_value<PP_GT(t)> {
        return (remove_reference_impl<PP_GT(t)>::value);
    });

PP_CIA get_value = [](concepts::value auto&& v) -> decltype(auto)
{
    return get_type_value(PP_DT(v));
};
}

constexpr decltype(auto) operator*(PP::concepts::value auto&& v) noexcept
{
    return PP::get_value(PP_F(v));
}

constexpr decltype(auto) operator-(
    PP::concepts::type auto&& t) noexcept requires requires
{
    ::PP::get_type_value(PP_F(t));
}
{
    return PP::get_type_value(PP_F(t));
}

#define PP_GV(x) (-PP_DT(x))
#define PP_CV(x) (::PP::value<PP_GV(x)>)
#define PP_CV_MEMBER(x, member) (::PP::value<PP_GV(x).member>)
#define PP_GV_TYPE(x) PP_DT(PP_GV(x))

constexpr auto operator==(PP::concepts::value auto&& x,
                          PP::concepts::value auto&& y)
{
    return PP::value<PP_GV(x) == PP_GV(y)>;
}
constexpr auto operator!=(PP::concepts::value auto&& x,
                          PP::concepts::value auto&& y)
{
    return PP::value<PP_GV(x) != PP_GV(y)>;
}
constexpr auto operator<(PP::concepts::value auto&& x,
                         PP::concepts::value auto&& y)
{
    return PP::value<PP_GV(x) < PP_GV(y)>;
}
constexpr auto operator<=(PP::concepts::value auto&& x,
                          PP::concepts::value auto&& y)
{
    return PP::value<PP_GV(x) <= PP_GV(y)>;
}
constexpr auto operator>(PP::concepts::value auto&& x,
                         PP::concepts::value auto&& y)
{
    return PP::value<(PP_GV(x) > PP_GV(y))>;
}
constexpr auto operator>=(PP::concepts::value auto&& x,
                          PP::concepts::value auto&& y)
{
    return PP::value<(PP_GV(x) >= PP_GV(y))>;
}
constexpr auto operator+(PP::concepts::value auto&& x,
                         PP::concepts::value auto&& y)
{
    return PP::value<PP_GV(x) + PP_GV(y)>;
}
constexpr auto operator-(PP::concepts::value auto&& x,
                         PP::concepts::value auto&& y)
{
    return PP::value<PP_GV(x) - PP_GV(y)>;
}
constexpr auto operator*(PP::concepts::value auto&& x,
                         PP::concepts::value auto&& y)
{
    return PP::value<PP_GV(x) * PP_GV(y)>;
}
constexpr auto operator/(PP::concepts::value auto&& x,
                         PP::concepts::value auto&& y)
{
    return PP::value<PP_GV(x) / PP_GV(y)>;
}
constexpr auto operator%(PP::concepts::value auto&& x,
                         PP::concepts::value auto&& y)
{
    return PP::value<PP_GV(x) % PP_GV(y)>;
}
constexpr auto operator&(PP::concepts::value auto&& x,
                         PP::concepts::value auto&& y)
{
    return PP::value<PP_GV(x) & PP_GV(y)>;
}
constexpr auto operator|(PP::concepts::value auto&& x,
                         PP::concepts::value auto&& y)
{
    return PP::value<PP_GV(x) | PP_GV(y)>;
}
constexpr auto operator-(PP::concepts::value auto&& x)
{
    return PP::value<-PP_GV(x)>;
}
constexpr auto operator!(PP::concepts::value auto&& x)
{
    return PP::value<!PP_GV(x)>;
}
constexpr auto operator&&(PP::concepts::value auto&& x,
                          PP::concepts::value auto&& y)
{
    return PP::value < PP_GV(x) && PP_GV(y) > ;
}
constexpr auto operator||(PP::concepts::value auto&& x,
                          PP::concepts::value auto&& y)
{
    return PP::value < PP_GV(x) || PP_GV(y) > ;
}

constexpr auto operator<=(PP::concepts::type auto&& x,
                          PP::concepts::type auto&& y) requires requires
{
    -x;
    -y;
}
{
    return -x <= -y;
}

namespace PP
{
PP_CIA to_value_t = [](concepts::value auto&& x)
{
    return value<PP_GV(x)>;
};
}

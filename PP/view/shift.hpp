#pragma once
#include <PP/size_t.hpp>
#include <PP/view/pair.hpp>

namespace PP::view
{
struct shift
{
    size_t value;
};
}

namespace PP
{
inline namespace literals
{
constexpr auto operator""_s(unsigned long long value)
{
    return view::shift(value);
}
}
}

constexpr auto operator>>(PP::view::shift offset, PP::concepts::view auto&& v)
{
    return PP::view::pair(PP::view::begin_(PP_F(v)) + offset.value,
                          PP::view::end_(PP_F(v)));
}
constexpr auto operator<<(PP::concepts::view auto&& v, PP::view::shift offset)
{
    return PP::view::pair(PP::view::begin_(PP_F(v)),
                          PP::view::end_(PP_F(v)) - offset.value);
}

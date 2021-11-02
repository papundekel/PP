#pragma once
#include "concepts/integer.hpp"
#include "to_chars.hpp"
#include "view/shift.hpp"

#include <iosfwd>

namespace PP
{
template <typename Char>
class ostream_basic
{
public:
    constexpr virtual void write(Char c) noexcept = 0;
};

using ostream = ostream_basic<char>;

extern ostream& cout;
}

template <typename Char>
constexpr auto& operator<<(PP::ostream_basic<Char>& out, Char c) noexcept
{
    out.write(c);
    return out;
}

template <typename Char>
constexpr auto& operator<<(PP::ostream_basic<Char>& out,
                           PP::concepts::view auto&& v) noexcept
{
    for (auto&& c : v)
        out.write(PP_F(c));
    return out;
}

template <typename Char, size_t N>
constexpr auto& operator<<(PP::ostream_basic<Char>& out,
                           const Char (&arr)[N]) noexcept
{
    return out << (arr << PP::view::shift(1));
}

template <typename Char>
constexpr auto& operator<<(PP::ostream_basic<Char>& out,
                           PP::concepts::integer auto number) noexcept
{
    Char buffer[32];
    auto begin = PP::to_chars(buffer, number);
    return out << PP::view::pair(begin, PP::view::end_(buffer));
}

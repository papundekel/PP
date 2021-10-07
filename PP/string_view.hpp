#pragma once
#include <iosfwd>

#include "size_t.hpp"
#include "view/equal.hpp"
#include "view/pair.hpp"
#include "view/shift.hpp"

namespace PP
{
///
/// @brief Replacement for @ref std::string_view
///
template <typename CharT>
class basic_string_view : public view::pair_pointer<const CharT>
{
public:
    constexpr basic_string_view(const CharT* begin, const CharT* end) noexcept
        : view::pair_pointer<const CharT>(begin, end)
    {}
    constexpr basic_string_view(concepts::view auto&& v) noexcept
        : basic_string_view(view::begin(PP_F(v)), view::end(PP_F(v)))
    {}
    template <size_t N>
    constexpr basic_string_view(const CharT (&arr)[N]) noexcept
        : basic_string_view(arr << 1_s)
    {}
};

using string_view = basic_string_view<char>;

inline namespace literals
{
constexpr auto operator""_sv(const char* s, size_t l)
{
    return string_view(s, s + l);
}
}
}

std::ostream& operator<<(std::ostream& out, PP::string_view sv);

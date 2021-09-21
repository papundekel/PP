#pragma once
#include <iosfwd>

#include "any_view.hpp"
#include "concepts/integer.hpp"
#include "containers/array.hpp"
#include "to_chars.hpp"

namespace PP
{
class ostream
{
public:
	constexpr virtual void write(char c) noexcept = 0;
};

extern ostream& cout;
}

constexpr PP::ostream& operator<<(PP::ostream& out, char c) noexcept
{
	out.write(c);
	return out;
}

constexpr PP::ostream& operator<<(PP::ostream& out,
                                  PP::concepts::view auto&& v) noexcept
{
	for (char c : v)
		out.write(c);
	return out;
}

constexpr PP::ostream& operator<<(PP::ostream& out,
                                  PP::concepts::integer auto number) noexcept
{
	char buffer[32];
	auto end = PP::to_chars(buffer, number);
	return out << (PP::view::pair(PP::view::begin(buffer), end));
}

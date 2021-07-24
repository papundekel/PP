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

constexpr ostream& operator<<(ostream& out, char c) noexcept
{
	out.write(c);
	return out;
}

constexpr ostream& operator<<(ostream& out, concepts::view auto&& v) noexcept
{
	for (char c : v)
		out.write(c);
	return out;
}

constexpr ostream& operator<<(ostream& out,
                              concepts::integer auto number) noexcept
{
	char buffer[32];
	auto end = to_chars(buffer, number);
	return out << (simple_view(view::begin(buffer), end));
}

extern ostream& cout;
}

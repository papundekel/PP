#pragma once
#include "integer.hpp"
#include "output_basic.hpp"

template <size_t s>
class Z
{
	static_assert(s >= 2, "field Z: can't have less than 2 elements");

public:
	size_t value;

	template <integer I>
	Z(I value)
		: value(value % s)
	{}
	Z operator+(Z other) const
	{
		return value + other.value;
	}
	Z& operator+=(Z other)
	{
		*this = *this + other;
		return *this;
	}
	Z operator-() const
	{
		return s - value;
	}
	Z operator-(Z other) const
	{
		return value + s - other.value;
	}
	Z& operator-=(Z other)
	{
		*this = *this - other;
		return *this;
	}
	Z& operator--()
	{
		*this -= 1;
		return *this;
	}
	Z operator--(int)
	{
		auto temp = *this;
		--*this;
		return temp;
	}
	Z& operator++()
	{
		*this += 1;
		return *this;
	}
	Z operator++(int)
	{
		auto temp = *this;
		++*this;
		return temp;
	}
	Z operator*(Z other)
	{
		return value * other.value;
	}
	Z& operator*=(Z other)
	{
		*this = *this * other;
		return *this;
	}
};

template <size_t s>
char* to_chars(char* begin, char* end, Z<s> z)
{
	return to_chars(begin, end, z.value);
}
#pragma once
#include "integer_unsigned.hpp"
#include "int.hpp"
#include <cmath>

class Q
{
	void simplify();
public:
	using intmax = diff_t;
	using uintmax = size_t;

	 intmax num;
	uintmax den;

	Q(intmax num);
	Q(intmax num, uintmax den);
	Q(double f);

	explicit operator intmax();
	explicit operator double();

	Q& operator+=(const Q& rhs);
	Q& operator-=(const Q& rhs);
	Q& operator*=(const Q& rhs);
	Q& operator/=(const Q& rhs);

	Q operator+(const Q& rhs) const;
	Q operator-(const Q& rhs) const;
	Q operator*(const Q& rhs) const;
	Q operator/(const Q& rhs) const;

	bool is_integer() const;

	static constexpr uintmax float_precision = 100000;
};

template <typename I>
requires integer(type<I>{})
Q pow(const Q& q, I exp)
{
	Q::intmax num_pow = pow(q.num, abs(exp));
	Q::uintmax den_pow = pow(q.den, abs(exp));

	if constexpr (integer_unsigned(type<I>{}))
		return { num_pow, den_pow };
	else
	{
		if (exp >= 0)
			return { num_pow, den_pow };
		else
			return { static_cast<Q::intmax>(den_pow), static_cast<Q::uintmax>(num_pow) };
	}
}
#include "Q.hpp"
#include <numeric>
void Q::simplify()
{
	auto GCD = std::gcd(num, den);
	num /= GCD;
	den /= GCD;
}
Q::Q(Q::intmax num)
	: num(num)
	, den(1)
{}
Q::Q(Q::intmax num, Q::uintmax den)
	: num(num)
	, den(den)
{
	simplify();
}
Q::Q(double f)
	: num(f * float_precision)
	, den(float_precision)
{
	simplify();
}
Q::operator intmax()
{
	return num / den;
}
Q::operator double()
{
	return num / static_cast<double>(den);
}
bool Q::is_integer() const
{
	return den == 1;
}

Q& Q::operator+=(const Q& rhs)
{
	auto LCM = std::lcm(den, rhs.den);

	num = num * (LCM / den) + rhs.num * (LCM / rhs.den);
	den = LCM;
	simplify();
	return *this;
}
Q& Q::operator-=(const Q& rhs)
{
	auto LCM = std::lcm(den, rhs.den);

	num = num * (LCM / den) - rhs.num * (LCM / rhs.den);
	den = LCM;
	simplify();
	return *this;
}
Q& Q::operator*=(const Q& rhs)
{
	num *= rhs.num;
	den *= rhs.den;
	simplify();
	return *this;
}
Q& Q::operator/=(const Q& rhs)
{
	num *= rhs.den;
	den *= rhs.num;
	simplify();
	return *this;
}
Q Q::operator+(const Q& rhs) const
{
	auto LCM = std::lcm(den, rhs.den);

	return
	{ num * static_cast<Q::intmax>(LCM / den) + rhs.num * static_cast<Q::intmax>(LCM / rhs.den)
	, LCM };
}
Q Q::operator-(const Q& rhs) const
{
	auto LCM = std::lcm(den, rhs.den);

	return
	{ num * static_cast<Q::intmax>(LCM / den) - rhs.num * static_cast<Q::intmax>(LCM / rhs.den)
	, LCM };
}
Q Q::operator*(const Q& rhs) const
{
	return
	{ num * rhs.num
	, den * rhs.den };
}
Q Q::operator/(const Q& rhs) const
{
	return
	{ num * static_cast<Q::intmax>(rhs.den)
	, den * rhs.num };
}
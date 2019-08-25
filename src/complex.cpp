#include "complex.hpp"
#include <cmath>

namespace math
{
	complex::complex()
		: real(0)
		, imag(0)
	{}
	complex::complex(double real, double imag)
		: real(real)
		, imag(imag)
	{}

	complex complex::operator+(const complex& rhs)
	{
		return { real + rhs.real, imag + rhs.imag };
	}
	complex complex::operator-(const complex& rhs)
	{
		return { real - rhs.real, imag - rhs.imag };
	}
	complex complex::operator*(const complex& rhs)
	{
		return { real * rhs.real - imag * rhs.imag, imag * rhs.real + real * rhs.imag };
	}
	complex complex::operator/(const complex& rhs)
	{
		return complex { real * rhs.real + imag * rhs.imag, imag * rhs.real - real * rhs.imag } / (rhs.real * rhs.real + rhs.imag * rhs.imag);
	}
	complex complex::operator+(double rhs)
	{
		return { real + rhs, imag };
	}
	complex complex::operator-(double rhs)
	{
		return { real - rhs, imag };
	}
	complex complex::operator*(double rhs)
	{
		return { real * rhs, imag * rhs };
	}
	complex complex::operator/(double rhs)
	{
		return { real / rhs, imag / rhs };
	}
	complex& complex::operator+=(const complex& rhs)
	{
		real += rhs.real;
		imag += rhs.imag;
		return *this;
	}
	complex& complex::operator-=(const complex& rhs)
	{
		real -= rhs.real;
		imag -= rhs.imag;
		return *this;
	}
	complex& complex::operator*=(const complex& rhs)
	{
		double old_real = real;
		real = old_real * rhs.real - imag * rhs.imag;
		imag = imag * rhs.real + old_real * rhs.imag;
		return *this;
	}
	complex& complex::operator/=(const complex& rhs)
	{
		double old_real = real;
		double temp = rhs.real * rhs.real + rhs.imag * rhs.imag;
		real = (old_real * rhs.real + imag * rhs.imag) / temp;
		imag = (imag * rhs.real - old_real * rhs.imag) / temp;
		return *this;
	}
	complex& complex::operator+=(double rhs)
	{
		real += rhs;
		return *this;
	}
	complex& complex::operator-=(double rhs)
	{
		real -= rhs;
		return *this;
	}
	complex& complex::operator*=(double rhs)
	{
		real *= rhs;
		imag *= rhs;
		return *this;
	}
	complex& complex::operator/=(double rhs)
	{
		real /= rhs;
		imag /= rhs;
		return *this;
	}
	complex operator+(double lhs, const complex& rhs)
	{
		return { lhs + rhs.real, rhs.imag };
	}

	double abs(const complex& c)
	{
		return sqrt(c.real * c.real + c.imag * c.imag);
	}
}

math::complex operator"" _i(long double value)
{
	return { 0, static_cast<double>(value) };
}
math::complex operator"" _i(unsigned long long value)
{
	return { 0, static_cast<double>(value) };
}
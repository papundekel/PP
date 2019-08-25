#pragma once

namespace math
{
	struct complex
	{
		double real;
		double imag;

		complex();
		complex(double real, double imag = 0);

		complex operator+(const complex& rhs);
		complex operator-(const complex& rhs);
		complex operator*(const complex& rhs);
		complex operator/(const complex& rhs);
		complex operator+(double rhs);
		complex operator-(double rhs);
		complex operator*(double rhs);
		complex operator/(double rhs);

		complex& operator+=(const complex& rhs);
		complex& operator-=(const complex& rhs);
		complex& operator*=(const complex& rhs);
		complex& operator/=(const complex& rhs);
		complex& operator+=(double rhs);
		complex& operator-=(double rhs);
		complex& operator*=(double rhs);
		complex& operator/=(double rhs);
	};

	complex operator+(double lhs, const complex& rhs);

	double abs(const complex& c);
}

math::complex operator"" _i(long double value);
math::complex operator"" _i(unsigned long long value);
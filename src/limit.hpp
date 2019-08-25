#pragma once

template <typename T>
struct limit
{
	static constexpr T max = T();
	static constexpr T min = T();
	static constexpr T epsilon = T();
	static constexpr T infinity = T();
	static constexpr T NaN = T();
};
template <> struct limit<signed char>
{
	static constexpr signed char max =  127i8;
	static constexpr signed char min = -max - 1;
};
template <> struct limit<short>
{
	static constexpr short max =  32767i16;
	static constexpr short min = -max - 1;
};
template <> struct limit<int>
{
	static constexpr int max = 2147483647i32;
	static constexpr int min = -max - 1;
};
template <> struct limit<long long>
{
	static constexpr long long max =  9223372036854775807i64;
	static constexpr long long min = -max - 1;
};
template <> struct limit<unsigned char>
{
	static constexpr unsigned char max = 0xffui8;
	static constexpr unsigned char min = 0;
};
template <> struct limit<unsigned short>
{
	static constexpr unsigned short max = 0xffffui16;
	static constexpr unsigned short min = 0;
};
template <> struct limit<unsigned int>
{
	static constexpr unsigned int max = 0xffffffffui32;
	static constexpr unsigned int min = 0;
};
template <> struct limit<unsigned long long>
{
	static constexpr unsigned long long max = 0xffffffffffffffffui64;
	static constexpr unsigned long long min = 0;
};
template <> struct limit<float>
{
	static constexpr float epsilon = 1.192092896e-07f;
	static constexpr float infinity = 1e+300 * 1e+300;
	static constexpr float NaN = infinity * 0.f;
};
template <> struct limit<double>
{
	static constexpr double epsilon = 2.2204460492503131e-16;
	static constexpr double infinity = 1e+300 * 1e+300;
	static constexpr double NaN = infinity * 0.;
};
template <> struct limit<long double>
{
	static constexpr long double epsilon = 2.2204460492503131e-16l;
	static constexpr long double infinity = 1e+300l * 1e+300l;
	static constexpr long double NaN = infinity * 0.l;
};
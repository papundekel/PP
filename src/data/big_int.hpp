#pragma once
#include <type_traits>
#include <algorithm>
#include <functional>
#include <cstdint>
#include "range.hpp"
#include "integer_unsigned.hpp"
#include "const_t.hpp"

template <integer T>
constexpr uint8_t sign(const T* value)
{
	if constexpr (integer_unsigned<T>)
		return 0;
	else
		return reinterpret_cast<const uint8_t*>(value)[sizeof(T) - 1] >> 7 == 1 ? 255 : 0;
}

template <typename T>
constexpr auto lower_byte(T& x)
{
	if constexpr (const_t<T>)
		return reinterpret_cast<const uint8_t*>(&x);
	else
		return reinterpret_cast<	  uint8_t*>(&x);
}

template <typename T>
auto get_byte(T& x, size_t index)
{
	return lower_byte(x)[index];
}

template <size_t size>
class big_int;

template <size_t _size>
class big_int
{
	template <typename dest_t, typename source_t>
	static void copy(dest_t* dest, const source_t* source)
	{
		if constexpr (sizeof(source_t) < sizeof(dest_t))
		{
			memcpy(dest, source, sizeof(source_t));

			uint8_t value = 0;
			if constexpr (std::is_signed_v<source_t> && std::is_signed_v<dest_t>)
				value = sign(source);

			memset(reinterpret_cast<uint8_t*>(dest) + sizeof(source_t), value, sizeof(dest_t) - sizeof(source_t));
		}
		else
			memcpy(dest, source, sizeof(dest_t));
	}
public:
	class base_out_of_range {};
	class non_numeric_symbol {};
	class zero_division {};

	uint8_t bytes[_size];

	big_int()
	{}
	template <typename T, typename =
	std::enable_if_t<std::is_integer_v<T>>>
	big_int(const T& value)
	{
		copy(this, &value);
	}
	template <typename it, typename =
	std::enable_if_t<is_iterator_bi<it>>>
	big_int(range<it> r, int base)
	{
		memset(bytes, 0, _size);

		if (base >= 2 && base <= 36 && r.begin != r.end)
		{
			big_int i = 1ui8;

			auto f = [base, &i, this](it p)
			{
				if (*p != ' ')
				{
					if ((base <= 10 && *p < ('0' + base) && *p >= '0') || (base > 10 && (*p < ('a' + base - 10) && *p >= 'a' || *p < ('A' + base - 10) && *p >= 'A')))
					{
						if (*p != '0')
							*this += i * (*p < 'A' ? (*p - '0') : (*p < 'a' ? (*p - 'A' + 10i8) : (*p - 'a' + 10i8)));
						i *= base;
					}
					else
						throw non_numeric_symbol();
				}
			};

			for (; --r.end != r.begin; )
				f(r.end);

			if (*r.end != '+')
			{
				if (*r.end != '-')
					f(r.end);
				else
					*this = -*this;
			}
		}
		else
			throw base_out_of_range();
	}
	template <size_t arr_size>
	big_int(const char(&arr)[arr_size], int base)
		: big_int(arr, arr + arr_size - 1, base)
	{}
	
	template <typename T, typename =
	std::enable_if_t<std::is_integer_v<T>>>
	explicit operator T() const
	{
		T result;
		copy(&result, this);
		return result;
	}

	size_t size() const
	{
		return _size;
	}

	uint8_t& operator[](size_t index)
	{
		return bytes[index];
	}
	uint8_t operator[](size_t index) const
	{
		return bytes[index];
	}
	template <typename T>
	std::enable_if_t<std::is_integer_v<T>,
	big_int&> operator=(const T& rhs)
	{
		copy(this, &rhs);
		return *this;
	}
	big_int& operator++()
	{
		if ((1ui8 & *bytes) != 1ui8)
			*bytes |= 1ui8;
		else
			*this += 1ui8;
		return *this;
	}
	big_int operator++(int)
	{
		big_int result = *this;
		++(*this);
		return result;
	}
	big_int& operator--()
	{
		if ((1ui8 & *bytes) == 1ui8)
			*bytes ^= 1ui8;
		else
			*this += 0b11111111i8;
		return *this;
	}
	big_int operator--(int)
	{
		big_int result = *this;
		--(*this);
		return result;
	}
	big_int operator-() const
	{
		big_int result = *this;
		for (size_t i = 0; i != _size; ++i)
			result[i] = ~result[i];
		return ++result;
	}
	big_int operator<<(size_t shift) const
	{
		big_int result = *this;

		size_t a = shift / 8;
		size_t b = shift % 8;

		if (a <= _size)
		{
			memset(result.bytes, 0, a);

			uint8_t x = 0ui8;

			for (size_t i = 0; i != _size - a; ++i)
			{
				result[a + i] = static_cast<uint8_t>(bytes[i] << b) | x;
				x = bytes[i] >> (8 - b);
			}
		}
		else
			memset(result.bytes, 0, _size);
		return result;
	}
	big_int& operator<<=(size_t shift)
	{
		return *this = *this << shift;
	}
	big_int operator>>(size_t shift) const
	{
		big_int result = *this;

		size_t a = shift / 8;
		size_t b = shift % 8;
		auto s = sign(this);

		if (a <= _size)
		{
			memset(result.bytes + _size - a, s, a);
			uint8_t x = s << (8 - b);
			for (size_t i = _size - 1; i != a - 1; --i)
			{
				result[i - a] = static_cast<uint8_t>(bytes[i] >> b) | x;
				x = bytes[i] << (8 - b);
			}
		}
		else
			memset(result.bytes, s, _size);
		return result;
	}
	big_int& operator>>=(size_t shift)
	{
		return *this = *this >> shift;
	}
};

template <size_t size>
std::ostream& operator<<(std::ostream& cout, big_int<size> value)
{
	char buffer[128];
	value.to_chars(buffer, buffer + 128);
	cout << buffer;
	return cout;
}
template <size_t size>
std::istream& operator>>(std::istream& cin, big_int<size>& value)
{
	char buffer[128];
	cin >> buffer;
	value = big_int<size>(buffer, buffer + strlen(buffer), 10);
	return cin;
}

template <typename T, typename U>
std::enable_if_t<std::is_integer_v<T> && std::is_integer_v<U>,
T&> operator+=(T& lhs, const U& rhs)
{
	if constexpr (sizeof(T) > sizeof(U))
		return lhs += static_cast<T>(rhs);
	else
	{
		uint16_t sum = 0;

		auto sum_l = lower_byte(sum);

		auto i = lower_byte(lhs);
		auto j = lower_byte(rhs);

		for (; i != lower_byte(lhs) + sizeof(T); ++i, ++j)
		{
			sum += *i + *j;
			*i = *sum_l;
			sum >>= 8;
		}

		return lhs;
	}	
}
template <typename T, typename U, typename =
std::enable_if_t<std::is_integer_v<T> && std::is_integer_v<U>>>
auto operator+(const T& lhs, const U& rhs)
{
	if constexpr (sizeof(T) > sizeof(U))
		return lhs + static_cast<T>(rhs);
	else if constexpr (sizeof(T) < sizeof(U))
		return static_cast<U>(lhs) + rhs;
	else
	{
		big_int<sizeof(T)> result = lhs;
		return result += rhs;
	}
}
template <typename T, typename U, typename =
std::enable_if_t<std::is_integer_v<T> && std::is_integer_v<U>>>
auto operator-(const T& lhs, const U& rhs)
{
	return lhs + -rhs;
}
template <typename T, typename U>
std::enable_if_t<std::is_integer_v<T> && std::is_integer_v<U>,
T&> operator-=(T& lhs, const U& rhs)
{
	lhs += -rhs;
	return lhs;
}
template <typename T, typename U, typename =
std::enable_if_t<std::is_integer_v<T> && std::is_integer_v<U>>>
auto operator*(T lhs, U rhs)
{
	if constexpr (sizeof(T) > sizeof(U))
		return lhs * static_cast<T>(rhs);
	else if constexpr (sizeof(T) < sizeof(U))
		return static_cast<U>(lhs) * rhs;
	else
	{
		if (lhs != 0 && rhs != 0)
		{
			T temp;
			memset(&temp, 0, sizeof(T));

			while (rhs != 1ui8 && rhs != 255i8)
			{
				if ((*lower_byte(rhs) & 1ui8) == 0ui8)
				{
					lhs <<= 1;
					rhs >>= 1;
				}
				else
				{
					temp += lhs;
					*lower_byte(rhs) ^= 1ui8;
				}
			}

			if (rhs == 1ui8)
				return lhs + temp;
			else
				return -lhs + temp;
		}
		else
			return T(0);
	}	
}
template <typename T, typename U>
std::enable_if_t<std::is_integer_v<T> && std::is_integer_v<U>,
T&> operator*=(T& lhs, const U& rhs)
{
	lhs = lhs * static_cast<T>(rhs);
	return lhs;
}

template <typename T>
static std::pair<T, T> _div_helper(T lhs, T rhs)
{
	T result;
	memset(&result, 0, sizeof(T));

	bool minus = false;
	if (sign(&lhs) != 0ui8)
	{
		lhs = -lhs;
		minus = true;
	}
	if (sign(&rhs) != 0ui8)
	{
		rhs = -rhs;
		minus = !minus;
	}

	while (true)
	{
		size_t i = 0;
		for (; lhs >= (rhs << i); ++i);

		if (i == 0)
		{
			if (minus)
				return { -result, -lhs };
			else
				return {  result,  lhs };
		}

		lhs -= rhs << --i;
		lower_byte(result)[i / 8] |= (1ui8) << (i % 8);
	}
}
template <typename T, typename U, typename =
std::enable_if_t<std::is_integer_v<T> && std::is_integer_v<U>>>
auto operator/(const T& lhs, const U& rhs)
{
	if (rhs != 0ui8)
	{
		if constexpr (sizeof(T) > sizeof(U))
			return lhs / static_cast<T>(rhs);
		else if constexpr (sizeof(T) < sizeof(U))
			return static_cast<U>(lhs) / rhs;
		else
			return _div_helper(lhs, rhs).first;
	}
	else
		throw big_int<69>::zero_division();
}
template <typename T, typename U>
std::enable_if_t<std::is_integer_v<T> && std::is_integer_v<U>,
T&> operator/=(T& lhs, const U& rhs)
{
	lhs = lhs / static_cast<T>(rhs);
	return lhs;
}
template <typename T, typename U, typename =
std::enable_if_t<std::is_integer_v<T> && std::is_integer_v<U>>>
auto operator%(const T& lhs, const U& rhs)
{
	if (rhs != 0ui8)
	{
		if constexpr (sizeof(T) > sizeof(U))
			return lhs % static_cast<T>(rhs);
		else if constexpr (sizeof(T) < sizeof(U))
			return static_cast<U>(lhs) % rhs;
		else
			return _div_helper(lhs, rhs).second;
	}
	else
		throw big_int<69>::zero_division();
}
template <typename T, typename U>
std::enable_if_t<std::is_integer_v<T> && std::is_integer_v<U>,
T&> operator%=(T& lhs, const U& rhs)
{
	lhs = lhs % static_cast<T>(rhs);
	return lhs;
}
template <typename T, typename U, typename =
std::enable_if_t<std::is_integer_v<T> && std::is_integer_v<U>>>
bool operator==(const T& lhs, const U& rhs)
{
	if constexpr (sizeof(T) > sizeof(U))
		return lhs == static_cast<T>(rhs);
	else if constexpr (sizeof(T) < sizeof(U))
		return static_cast<U>(lhs) == rhs;
	else
	{
		size_t i = 0;
		for (; i != sizeof(T) && get_byte(lhs, i) == get_byte(rhs, i); ++i);
		return i == sizeof(T);
	}
}
template <typename T, typename U, typename =
std::enable_if_t<std::is_integer_v<T> && std::is_integer_v<U>>>
bool operator!=(const T& lhs, const U& rhs)
{
	return !(lhs == rhs);
}
template <typename T, typename U, typename = 
std::enable_if_t<std::is_integer_v<T> && std::is_integer_v<U>>>
bool operator<(const T& lhs, const U& rhs)
{
	if constexpr (sizeof(T) > sizeof(U))
		return lhs < static_cast<T>(rhs);
	else if constexpr (sizeof(T) < sizeof(U))
		return static_cast<U>(lhs) < rhs;
	else
	{
		auto lhs_s = sign(&lhs);
		auto rhs_s = sign(&rhs);
		if (lhs_s == 0 && rhs_s != 0)
			return false;
		if (lhs_s != 0 && rhs_s == 0)
			return true;
		else
		{
			size_t i = sizeof(T) - 1;
			for (; i != -1 && get_byte(lhs, i) == get_byte(rhs, i); --i);
			return i != -1 && get_byte(lhs, i) < get_byte(rhs, i);
		}
	}
}
template <typename T, typename U, typename =
std::enable_if_t<std::is_integer_v<T> && std::is_integer_v<U>>>
bool operator>(const T& lhs, const U& rhs)
{
	return rhs < lhs;
}
template <typename T, typename U, typename =
std::enable_if_t<std::is_integer_v<T> && std::is_integer_v<U>>>
bool operator<=(const T& lhs, const U& rhs)
{
	return !(lhs > rhs);
}
template <typename T, typename U, typename =
std::enable_if_t<std::is_integer_v<T> && std::is_integer_v<U>>>
bool operator>=(const T& lhs, const U& rhs)
{
	return !(lhs < rhs);
}
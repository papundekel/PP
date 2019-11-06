#pragma once
#include <initializer_list>
#include "memcopy.hpp"
#include "copy.hpp" 
#include "fill.hpp"
#include "arithmetic.hpp"
#include "conditional.hpp"
#include <cmath>

template <size_t m, size_t n, arithmetic T = float>
class matrix
{
	static constexpr size_t size = m * n;
	static constexpr bool row_column = m == 1 || n == 1;
	static constexpr bool is_single = m == 1 && n == 1;
public:
	using column = matrix<m, 1, T>;
	using	 row = matrix<1, n, T>;
	using single = matrix<1, 1, T>;

	T elements[m * n];

	matrix()
		: elements()
	{}
	explicit(!is_single) matrix(T value)
	{
		fill(range(elements), value);
	}
	template <typename F>
	matrix(F f)
	{
		for (size_t i = 0; i != m; ++i)
			for (size_t j = 0; j != n; ++j)
				(*this)(i, j) = f(i, j);
	}
	matrix(const std::initializer_list<T>& list)
	{
		copy(range(list), range(elements));
	}
	static matrix identity()
	{
		static_assert(m == n);
		matrix result(0);
		for (size_t i = 0; i != m; ++i)
			result(i, i) = 1;
		return result;
	}
	operator T() requires is_single
	{
		return elements[0];
	}
	auto begin()
	{
		return elements;
	}
	auto begin() const
	{
		return elements;
	}
	auto end()
	{
		return elements + size;
	}
	auto end() const
	{
		return elements + size;
	}
	auto& operator()(size_t i)
	{
		return elements[i];
	}
	auto operator()(size_t i) const
	{
		return elements[i];
	}
	auto& operator()(size_t i, size_t j)
	{
		return elements[i * n + j];
	}
	auto operator()(size_t i, size_t j) const
	{
		return elements[i * n + j];
	}
	auto operator+(const matrix& rhs) const
	{
		return matrix([this, rhs](size_t i, size_t j)
		{
			return (*this)(i, j) + rhs(i, j);
		});
	}
	auto operator*(T rhs) const
	{
		return matrix([this, rhs](size_t i, size_t j)
		{
			return (*this)(i, j) * rhs;
		});
	}
	auto operator/(T rhs) const
	{
		return matrix([this, rhs](size_t i, size_t j)
		{
			return (*this)(i, j) / rhs;
		});
	}
	T norm() requires (n == 1)
	{
		return std::sqrt(std::abs(transposed() * *this));
	}
	template <size_t o>
	auto operator*(const matrix<n, o, T>& rhs) const// -> conditional<m == 1 && o == 1, T, matrix<m, o, T>>
	{
		if constexpr (m == 1 && o == 1)
		{
			auto value = T();
			for (size_t k = 0; k != n; ++k)
				value += elements[k] * rhs.elements[k];
			return value;
		}
		else
		{
			return matrix<m, o, T>([this, rhs](size_t i, size_t j)
			{
				auto value = T();
				for (size_t k = 0; k != n; ++k)
					value += (*this)(i, k) * rhs(k, j);
				return value;
			});
		}		
	}
	matrix<n, m, T> transposed()
	{
		return matrix<n, m, T>([this](size_t i, size_t j)
		{
			return (*this)(j, i);
		});
	}
	constexpr size_t width()
	{	return n;	}
	constexpr size_t height()
	{	return m;	}
};

template <size_t m> using vector = matrix<m, 1>;

#include "output_basic.hpp"

template <size_t m, size_t n, typename T>
char* to_chars(char* begin, char* end, const matrix<m, n, T>& A)
{
	size_t max_len = 0;
	for (auto i : A)
		max_len = max(max_len, output_length(i));

	for (int i = 0; i != m; ++i)
	{
		_output(copy_char, '|');
		for (int j = 0; j != n; ++j)
		{
			auto spaces_count = max_len - output_length(A(i, j));
			for (int i = 0; i != spaces_count; ++i)
				_output(copy_char, ' ');
			_output(to_chars, A(i, j));
			if (j != n - 1)
				_output(copy_char, ' ');
		}
		_output(copy_char, '|');
		if (i != m - 1)
			_output(copy_char, '\n');
	}
	return begin;
}
#pragma once
#include "int.hpp"
constexpr size_t byte_size = 8;

static_assert(byte_size > 1);
namespace detail
{
	constexpr size_t byte_size_bits()
	{
		size_t i = 1;
		for (size_t j = 2; j < byte_size; j <<= 1, ++i);
		return i;
	}
}
constexpr size_t byte_size_bits = detail::byte_size_bits();

struct bit_ptr
{
	unsigned char* byte;
	unsigned char offset : byte_size_bits;

	bit_ptr(const void* ptr, size_t offset);
	bit_ptr& operator++();
	bit_ptr operator++(int);
	bit_ptr& operator--();
	bit_ptr operator--(int);
	bit_ptr operator+(diff_t diff) const;
	bit_ptr operator-(diff_t diff) const;
	diff_t operator-(bit_ptr bit) const;
	bool operator==(bit_ptr bit) const;
	bool operator!=(bit_ptr bit) const;
	bool operator<(bit_ptr bit) const;
};

class bit_ref
{
	bit_ptr bit;
	template <size_t i>
	constexpr unsigned char& byte() const
	{
		static_assert(i <= 1, "owns max two bytes");
		return bit.byte[i];
	}
public:
	operator bool() const;
	bit_ref(bit_ptr bit);
	bit_ref(const bit_ref& copy);
	bit_ref(bit_ref&& move) noexcept;
	bit_ref& operator=(const bit_ref& value);
	bit_ref& operator=(bit_ref&& value) noexcept;
	bit_ref operator=(bool value);

	bool operator==(const bit_ref& other) const;
	bool operator!=(const bit_ref& other) const;
};

class bit_it
{
	bit_ptr bit;
public:
	bit_it(bit_ptr bit);
	bit_ref operator*() const;
	bit_ref operator[](diff_t offset) const;
	bit_it& operator++();
	bit_it operator++(int);
	bit_it& operator--();
	bit_it operator--(int);
	bit_it operator+(diff_t other) const;
	bit_it operator-(diff_t other) const;
	diff_t operator-(bit_it other) const;
	bool operator==(bit_it other) const;
	bool operator!=(bit_it other) const;
	bool operator<(bit_it other) const;
};

class const_bit_it
{
	bit_ptr bit;
public:
	const_bit_it(bit_ptr bit);
	const bit_ref operator*() const;
	const bit_ref operator[](diff_t offset) const;
	const_bit_it& operator++();
	const_bit_it operator++(int);
	const_bit_it& operator--();
	const_bit_it operator--(int);
	const_bit_it operator+(diff_t other) const;
	const_bit_it operator-(diff_t other) const;
	diff_t operator-(const_bit_it other) const;
	bool operator==(const_bit_it other) const;
	bool operator!=(const_bit_it other) const;
	bool operator<(const_bit_it other) const;
};
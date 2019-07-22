#pragma once
#include "int.hpp"

template <typename T>
class iterator_random_access
{
	using it_RA = iterator_random_access;
	T* ptr;
public:
	iterator_random_access(T* pointer)
		: ptr(pointer)
	{}
	T* operator->() const
	{
		return ptr;
	}
	T& operator*() const
	{
		return *ptr;
	}
	T& operator[](diff_t offset) const
	{
		return ptr[offset];
	}
	it_RA& operator++()
	{
		++ptr;
		return *this;
	}
	it_RA operator++(int)
	{
		auto temp = *this;
		++ptr;
		return temp;
	}
	it_RA& operator--()
	{
		--ptr;
		return *this;
	}
	it_RA operator--(int)
	{
		auto temp = *this;
		--ptr;
		return temp;
	}
	it_RA operator+(diff_t other) const
	{
		return ptr + other;
	}
	it_RA operator-(diff_t other) const
	{
		return ptr - other;
	}
	diff_t operator-(it_RA other) const
	{
		return ptr - other.ptr;
	}
	bool operator==(it_RA other) const
	{
		return ptr == other.ptr;
	}
	bool operator!=(it_RA other) const
	{
		return ptr != other.ptr;
	}
	bool operator<(it_RA other) const
	{
		return ptr < other.ptr;
	}
};
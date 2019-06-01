#pragma once
#include "move.hpp"
#include "swap.hpp"

template <typename T = char>
class bim
{
public:
	T* handle;

	bim()
		: handle(new T)
	{
		print("bim def ctor");
	}
	bim(const bim& bim)
		: handle(new T(*bim.handle))
	{
		print("bim copy ctor");
	}
	bim(bim&& bim) noexcept
		: handle(bim.handle)
	{
		bim.handle = nullptr;
		print("bim move ctor");
	}
	bim(const T& value)
		: handle(new T(value))
	{
		print("bim value copy ctor");
	}
	bim(T&& value)
		: handle(new T(move(value)))
	{
		print("bim value move ctor");
	}
	bim& operator=(const bim& right)
	{
		*handle = *right.handle;
		print("bim copy assignment");
		return *this;
	}
	bim& operator=(bim&& right)
	{
		swap(handle, right.handle);

		print("bim move assignment");
		return *this;
	}
	~bim()
	{
		if (handle)
			print("bim dtor");
		else
			print("bim null dtor");

		delete handle;
	}
	T& operator*() &
	{
		return *handle;
	}
	const T& operator*() const&
	{
		return *handle;
	}
	T&& operator*() &&
	{
		return move(*handle);
	}
	const T&& operator*() const&&
	{
		return move(*handle);
	}
};
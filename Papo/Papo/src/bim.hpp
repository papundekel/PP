#pragma once
#include "move.hpp"
#include "swap.hpp"
#include "output.hpp"

template <typename T = char>
class bim
{
public:
	T data;

	bim()
		: data()
	{
		print("bim def ctor");
	}
	bim(const bim& bim)
		: data(bim.data)
	{
		print("bim copy ctor");
	}
	bim(bim&& bim) noexcept
		: data(move(bim.data))
	{
		print("bim move ctor");
	}
	bim& operator=(const bim& right)
	{
		data = right.data;
		print("bim copy assignment");
		return *this;
	}
	bim& operator=(bim&& right)
	{
		data = move(right.data);
		print("bim move assignment");
		return *this;
	}
	~bim()
	{
		print("bim dtor");
	}
	operator T()
	{
		return data;
	}
};
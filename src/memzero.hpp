#pragma once
#include "mem_set.hpp"

template <typename T>
T* memzero(T& obj)
{
	return reinterpret_cast<T*>(mem_set(&obj, 1, 0));
}
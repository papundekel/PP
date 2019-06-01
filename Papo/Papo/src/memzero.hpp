#pragma once
#include "memset.hpp"

template <typename T>
T* memzero(T& obj)
{
	return reinterpret_cast<T*>(memset(reinterpret_cast<void*>(&obj), 0, sizeof(obj)));
}
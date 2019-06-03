#pragma once
#include <cstring>

template <typename T>
T* mem_set(T* ptr, size_t count, char value)
{
	return reinterpret_cast<T*>(memset(ptr, count * sizeof(T), value));
}
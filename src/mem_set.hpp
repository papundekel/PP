#pragma once
#include <cstring>

template <typename T>
inline T* mem_set(T* ptr, size_t count, char value)
{
	return reinterpret_cast<T*>(memset(ptr, count * sizeof(T), value));
}
template <typename T, size_t s>
inline T* mem_set(T(&arr)[s], char value)
{
	return mem_set(arr, s, value);
}
#pragma once
#include <cstring>

template <typename T>
T* memcopy(T* destination, const T* source, size_t count)
{
	return reinterpret_cast<T*>(memcpy(destination, source, count * sizeof(T)));
}

template <typename T, size_t N>
T* memcopy(T* destination, const T(&source)[N])
{
	return memcopy(destination, source, sizeof(source));
}
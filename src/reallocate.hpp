#pragma once
#include <cstdlib>
#include "exception.hpp"

template <typename T>
void reallocate(T*& where, size_t count)
{
	T* old = where;
	if (!(where = reinterpret_cast<T*>(realloc(where, count * sizeof(T)))))
	{
		free(old);
		throw exception("realloc failed");
	}
}
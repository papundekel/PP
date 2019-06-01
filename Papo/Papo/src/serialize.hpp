#pragma once
#include "void_t.hpp"
#include "declval.hpp"
#include "array.hpp"
#include <corecrt_memory.h>
template <typename T>
concept serializable = requires(T t)
{
	t.serialize();
};

template <typename T>
auto serialize(const T& object)
{
	if constexpr (serializable<T>)
		return object.serialize();
	else
	{
		char buffer[sizeof(T)];
		memcpy(buffer, &object, sizeof(T));
		return array(buffer);
	}
}
#pragma once
#include "signed_integer.hpp"
#include "unsigned_integer.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept integer = signed_integer<T> || unsigned_integer<T>;
	}
}

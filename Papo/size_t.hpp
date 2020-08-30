#pragma once
#include <cstddef>
#include <type_traits>

namespace PPmatrix
{
	using size_t = std::size_t;
	using ssize_t = std::make_signed_t<size_t>;
}

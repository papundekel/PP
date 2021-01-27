#pragma once
#include <memory>

#include "alignment_of.hpp"
#include "array.hpp"
#include "functional/operators.hpp"
#include "max_default.hpp"
#include "size_of.hpp"
#include "tuple_map_to_array.hpp"

namespace PP
{
	template <typename... T>
	class variant
	{
		static constexpr auto find_max(auto parameter_map) noexcept
		{
			return *max_default(parameter_map < type_tuple<T...>);
		}

		static constexpr auto alignment = find_max(alignment_of);
		static constexpr auto size = find_max(size_of);

		alignas(alignment) array<char, size> buffer;

	public:
		
	};
}

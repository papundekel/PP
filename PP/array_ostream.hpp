#pragma once
#include "array_vector.hpp"
#include "basic_ostream.hpp"

namespace PP
{
	namespace detail
	{
		template <std::size_t count>
		struct array_ostream_helper
		{
			template <typename T>
			using help = array_vector<T, count, true>;
		};
	}

	template <std::size_t count>
	using array_ostream = basic_ostream<detail::array_ostream_helper<count>::template help>;
}

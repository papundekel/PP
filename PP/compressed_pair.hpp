#pragma once
#include <type_traits>

namespace PP
{
	namespace detail
	{
		struct empty {};

		// saves memory when one type from the pair is empty
		//
		// useful in simple_view with unbounded, where the only
		// information is the type of its end iterator, not data
		//
		// for the same reason also in transform_iterator,
		// if the transform is a captureless lambda or other empty functor

		template <typename First, typename Second>
		struct compressed_pair_nonempty
		{
			First first;
			Second second;
		};
		template <typename Empty, typename Second>
		struct compressed_pair_empty_first
		{
			[[no_unique_address]]
			Empty first;

			Second second;
		};
		template <typename First, typename Empty>
		struct compressed_pair_empty_second
		{
			First first;

			[[no_unique_address]]
			Empty second{};
		};

		template <typename First, typename Second>
		constexpr auto compressed_pair_dispatch()
		{
			if constexpr (std::is_empty_v<First>)
				return std::type_identity<compressed_pair_empty_first<First, Second>>{};
			else if constexpr (std::is_empty_v<Second>)
				return std::type_identity<compressed_pair_empty_second<First, Second>>{};
			else
				return std::type_identity<compressed_pair_nonempty<First, Second>>{};
		}
	}

	template <typename First, typename Second>
	using compressed_pair = typename decltype(detail::compressed_pair_dispatch<First, Second>())::type;
}

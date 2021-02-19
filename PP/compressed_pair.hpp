#pragma once
#include "concepts/empty.hpp"
#include "template_t.hpp"

namespace PP
{
	namespace detail
	{
		// saves memory when one type from the pair is empty
		//
		// useful in simple_view with unbounded, where the only
		// information is the type of its end iterator, not data
		//
		// for the same reason also in transform_iterator,
		// if the transform is a capture-less lambda or other empty functor

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
			Empty second;
		};

		constexpr auto compressed_pair_dispatch_template(concepts::type auto first, concepts::type auto second)
		{
			if constexpr (is_empty(PP_COPY_TYPE(first)))
				return Template<compressed_pair_empty_first>;
			else if constexpr (is_empty(PP_COPY_TYPE(second)))
				return Template<compressed_pair_empty_second>;
			else
				return Template<compressed_pair_nonempty>;
		}
		constexpr auto compressed_pair_dispatch(concepts::type auto first, concepts::type auto second)
		{
			return compressed_pair_dispatch_template(first, second)(first, second);
		}
	}

	template <typename First, typename Second>
	using compressed_pair = PP_GET_TYPE(detail::compressed_pair_dispatch(type<First>, type<Second>));
}

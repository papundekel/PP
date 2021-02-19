#pragma once
#include "concepts/same_except_cvref.hpp"
#include "construct_pack.hpp"
#include "functional/applier.hpp"
#include "functional/apply_partially.hpp"
#include "functional/operators.hpp"
#include "simple_view.hpp"
#include "tuple_any.hpp"
#include "tuple_for_each.hpp"
#include "tuple_map.hpp"
#include "tuple_std.hpp"
#include "view.hpp"

namespace PP
{
	template <typename... Iterators>
	class zip_iterator
	{
		template <typename...>
		friend class zip_iterator;

		tuple<Iterators...> iterators;

	public:
		constexpr zip_iterator(placeholder_t, auto&&... iterators)
			: iterators(placeholder, PP_FORWARD(iterators)...)
		{}

		constexpr auto operator*() const
		{
			return der + iterators;
		}
		constexpr auto& operator+=(ptrdiff_t offset)
		{
			tuple_for_each(value_true, pas(partial_tag, value_1, offset), iterators);
			return *this;
		}
		constexpr auto& operator-=(ptrdiff_t offset)
		{
			tuple_for_each(value_true, mas(partial_tag, value_1, offset), iterators);
			return *this;
		}
		template <typename... IteratorsOther>
		requires (sizeof...(Iterators) == sizeof...(IteratorsOther))
		constexpr bool operator==(const zip_iterator<IteratorsOther...>& other) const noexcept
		{
			return *eql || iterators ^ other.iterators;
		}

		constexpr auto operator[](concepts::value auto i) const
		{
			return iterators[i];
		}
	};
	template <typename... Iterators>
	zip_iterator(placeholder_t, Iterators...) -> zip_iterator<Iterators...>;

	PP_FUNCTOR(make_zip_iterator, auto&&... iterators)
	{
		return zip_iterator(placeholder, PP_FORWARD(iterators)...);
	}};

	PP_FUNCTOR(zip_view_pack, concepts::view auto&&... views)
	{
		return
			make_zip_iterator(view_begin(PP_FORWARD(views))...) ^
			make_zip_iterator(view_end  (PP_FORWARD(views))...);
	}};
}

#pragma once
#include "applier.hpp"
#include "apply_partially.hpp"
#include "concepts/same_except_cvref.hpp"
#include "construct_pack.hpp"
#include "operators.hpp"
#include "simple_view.hpp"
#include "tuple.hpp"
#include "tuple_all.hpp"
#include "tuple_any.hpp"
#include "tuple_for_each.hpp"
#include "tuple_map.hpp"
#include "tuple_std.hpp"
#include "tuple_zip_with.hpp"
#include "view.hpp"

namespace PP
{
	template <typename... Iterators>
	class zip_iterator : public tuple<Iterators...>
	{
		template <typename...>
		friend class zip_iterator;

	public:
		static constexpr char dont_make_array_star_operator{};

		constexpr zip_iterator(placeholder_t, auto&&... iterators)
			: tuple<Iterators...>(placeholder, PP_FORWARD(iterators)...)
		{}

		constexpr auto operator*() const
		{
			if constexpr ((concepts::iterator<Iterators> && ...))
				return der + *this;
			else
				return 0;
		}
		constexpr void step()
		{
			if constexpr ((concepts::iterator<Iterators> && ...))
				tuple_for_each(value_true, ipr, *this);
		}
		constexpr auto advance(ptrdiff_t offset)
		{
			if constexpr ((concepts::iterator_ra<Iterators> && ...))
				tuple_for_each(value_true,
							   pas(partial_tag, value_1, offset),
							   *this);
			else
				return 0;
		}
		template <typename... IteratorsOther>
		requires(sizeof...(Iterators) ==
				 sizeof...(IteratorsOther)) constexpr bool
		operator==(const zip_iterator<IteratorsOther...>& other) const noexcept
		{
			return *eql || tuple_zip_pack(*this, other);
		}
	};
	template <typename... Iterators>
	zip_iterator(placeholder_t, Iterators...) -> zip_iterator<Iterators...>;

	PP_FUNCTOR(make_zip_iterator, auto&&... iterators)
	{
		return zip_iterator(placeholder, PP_FORWARD(iterators)...);
	});

	PP_FUNCTOR(zip_view_pack, concepts::view auto&&... views)
	{
		return simple_view(make_zip_iterator(view_begin(PP_FORWARD(views))...),
						   make_zip_iterator(view_end(PP_FORWARD(views))...));
	});
}

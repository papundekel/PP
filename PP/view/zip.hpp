#pragma once
#include "../applier.hpp"
#include "../apply_partially.hpp"
#include "../concepts/same_except_cvref.hpp"
#include "../construct_pack.hpp"
#include "../containers/tuple.hpp"
#include "../containers/tuple_std.hpp"
#include "../operators.hpp"
#include "../tuple/all.hpp"
#include "../tuple/any.hpp"
#include "../tuple/for_each.hpp"
#include "../tuple/map.hpp"
#include "../tuple/zip_with.hpp"
#include "concept.hpp"
#include "pair.hpp"

namespace PP
{
template <typename... Iterators>
class zip_iterator : public tuple::container<Iterators...>
{
	template <typename...>
	friend class zip_iterator;

public:
	static constexpr char dont_make_array_star_operator{};

	constexpr zip_iterator(placeholder_t, auto&&... iterators)
	    : tuple::container<Iterators...>(placeholder, PP_F(iterators)...)
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
			tuple::for_each(value_true, ipr, *this);
	}
	constexpr auto advance(ptrdiff_t offset)
	{
		if constexpr ((concepts::iterator_ra<Iterators> && ...))
			tuple::for_each(value_true,
			                pas(partial_tag, value_1, offset),
			                *this);
		else
			return 0;
	}
	template <typename... IteratorsOther>
	requires(sizeof...(Iterators) == sizeof...(IteratorsOther)) constexpr bool
	operator==(const zip_iterator<IteratorsOther...>& other) const noexcept
	{
		return *eql || tuple::zip_pack(*this, other);
	}
};
template <typename... Iterators>
zip_iterator(placeholder_t, Iterators...) -> zip_iterator<Iterators...>;

PP_FUNCTOR(make_zip_iterator, auto&&... iterators)
{
	return zip_iterator(placeholder, PP_F(iterators)...);
});

PP_FUNCTOR(zip_view_pack, concepts::view auto&&... views)
{
	return simple_view(make_zip_iterator(view::begin(PP_F(views))...),
	                   make_zip_iterator(view::end(PP_F(views))...));
});
}

#pragma once
#include <initializer_list>

#include "compressed_pair.hpp"
#include "concepts/same_except_cvref.hpp"
#include "functor.hpp"
#include "ptrdiff_t.hpp"
#include "unbounded.hpp"
#include "view/concept.hpp"

namespace PP
{
template <typename Iterator, concepts::sentinel<Iterator> Sentinel = Iterator>
class simple_view
{
	compressed_pair<Iterator, Sentinel> pair;

public:
	constexpr simple_view()
	    : pair()
	{}
	constexpr simple_view(Iterator begin, Sentinel end)
	    : pair(begin, end)
	{}
	constexpr simple_view(concepts::view auto&& v) requires
	    concepts::different_except_cvref<simple_view, decltype(v)>
	    : simple_view(view::begin(PP_F(v)), view::end(PP_F(v)))
	{}
	constexpr simple_view(
	    const std::initializer_list<
	        apply_transform_t<remove_reference | iterator_base, Iterator>>& l)
	    : simple_view(l.begin(), l.end())
	{}
	constexpr auto begin() const
	{
		return pair.first;
	}
	constexpr auto end() const
	{
		return pair.second;
	}
	constexpr decltype(auto) operator[](ptrdiff_t index) const
	{
		return begin()[index];
	}
};
simple_view(concepts::view auto&& v)
    -> simple_view<PP_APPLY_TRANSFORM(view::type_begin_iterator, PP_DT(v)),
                   PP_APPLY_TRANSFORM(view::type_end_iterator, PP_DT(v))>;
template <typename T>
simple_view(const std::initializer_list<T>&) -> simple_view<const T*, const T*>;

template <typename T>
using pointer_view = simple_view<T*>;

PP_FUNCTOR(make_simple_view, concepts::view auto&& v)
{
	return simple_view(PP_F(v));
});
}

constexpr auto operator^(PP::concepts::iterator auto begin,
                         PP::concepts::sentinel<decltype(begin)> auto end)
{
	return PP::simple_view(begin, end);
}

constexpr auto operator|(PP::concepts::view auto&& v, PP::unbounded_t)
{
	return PP::view::begin(PP_F(v)) ^ PP::unbounded;
}

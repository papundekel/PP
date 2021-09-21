#pragma once
#include "../get_type.hpp"
#include "../get_value.hpp"
#include "../remove_cvref.hpp"
#include "../utility/move.hpp"
#include "../view/concept.hpp"

namespace PP
{
template <concepts::iterator Iterator, size_t Count>
class view_tuple
{
	Iterator begin;

public:
	constexpr view_tuple(concepts::value auto, Iterator begin) noexcept
	    : begin(move(begin))
	{}

	constexpr decltype(auto) operator[](concepts::value auto i) const noexcept
	{
		return begin[*i];
	};
	constexpr auto element(concepts::value auto i) const noexcept
	{
		return PP_DT(operator[](i));
	}
	constexpr auto tuple_count() const noexcept
	{
		return value<Count>;
	}
};
template <typename Iterator>
view_tuple(concepts::value auto count, Iterator)
    -> view_tuple<Iterator, *PP_CV(count)>;

constexpr auto make_view_tuple(concepts::value auto count,
                               concepts::iterator auto&& i) noexcept
{
	return view_tuple(count, PP_F(i));
}
constexpr auto make_view_tuple(concepts::value auto count,
                               concepts::view auto&& v) noexcept
{
	return make_view_tuple(count, view::begin(PP_F(v)));
}
}

#pragma once
#include <PP/compressed_pair.hpp>
#include <PP/concepts/same_except_cvref.hpp>
#include <PP/ptrdiff_t.hpp>
#include <PP/view/concept.hpp>
#include <PP/view/unbounded.hpp>

#include <initializer_list>

namespace PP::view
{
template <typename Iterator, concepts::sentinel<Iterator> Sentinel = Iterator>
class pair
{
    compressed_pair<Iterator, Sentinel> p;

public:
    constexpr pair()
        : p()
    {}
    constexpr pair(Iterator begin, Sentinel end)
        : p(begin, end)
    {}
    constexpr pair(concepts::view auto&& v) requires
        concepts::different_except_cvref<pair, decltype(v)>
        : pair(view::begin_(PP_F(v)), view::end_(PP_F(v)))
    {}
    constexpr pair(const std::initializer_list<
                   apply_transform_t<compose(remove_reference, iterator_base),
                                     Iterator>>& l)
        : pair(l.begin(), l.end())
    {}
    constexpr auto begin() const
    {
        return p.first;
    }
    constexpr auto end() const
    {
        return p.second;
    }
    constexpr decltype(auto) operator[](ptrdiff_t index) const
    {
        return begin()[index];
    }
};
pair(concepts::view auto&& v)
    -> pair<PP_APPLY_TRANSFORM(view::type_begin_iterator, PP_DT(v)),
            PP_APPLY_TRANSFORM(view::type_end_iterator, PP_DT(v))>;
template <typename T>
pair(const std::initializer_list<T>&) -> pair<const T*, const T*>;

template <typename T>
using pair_pointer = pair<T*>;

PP_CIA make_pair = [](concepts::view auto&& v)
{
    return pair(PP_F(v));
};
}

constexpr auto operator^(PP::concepts::iterator auto&& begin,
                         PP::concepts::sentinel<decltype(begin)> auto&& end)
{
    return PP::view::pair(begin, end);
}

constexpr auto operator|(PP::concepts::view auto&& v, PP::view::unbounded_t)
{
    return PP::view::begin_(PP_F(v)) ^ PP::view::unbounded;
}

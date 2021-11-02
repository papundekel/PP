#pragma once
#include "view.hpp"

namespace PP::view
{
template <typename I, typename E, typename J>
class chain_iterator
{
    I i;
    E e;
    J j;

public:
    constexpr chain_iterator(const I& i, const E& e, const J& j)
        : i(i)
        , e(e)
        , j(j)
    {}

    constexpr decltype(auto) operator*() const
    {
        if (i != e)
            return *i;
        else
            return *j;
    }

    constexpr decltype(auto) operator[](ptrdiff_t offset) const
    {
        if constexpr (PP::concepts::iterator_ra<I> &&
                      PP::concepts::iterator_ra<J>) {
            if (i != e)
                return i[offset];
            else
                return j[offset];
        }
    }

    constexpr void step()
    {
        if (i != e)
            ++i;
        else
            ++j;
    }

    constexpr auto advance(ptrdiff_t offset)
    {
        if constexpr (PP::concepts::iterator_ra<I> &&
                      PP::concepts::iterator_ra<J>) {
            auto first_sequence_diff = e - i;
            if (first_sequence_diff < offset) {
                i += first_sequence_diff;
                j += offset - first_sequence_diff;
            }
            else {
                i += offset;
            }
        }
        else
            return 0;
    }

    constexpr bool operator==(const chain_iterator& other) const
    {
        return i == other.i && e == other.e && j == other.j;
    }
    constexpr bool operator==(const auto& other) const
    {
        if (i != e)
            return false;
        else
            return j == other;
    }

    constexpr ptrdiff_t operator-(const chain_iterator& other) const
    {
        if (e == other.e)
            return (i - other.i) + (j - other.j);
        else
            return 0;
    }
};

template <typename I, typename E>
class chain_wrap
{
    compressed_pair<I, E> pair;

public:
    constexpr chain_wrap(const I& i, const E& e)
        : pair(i, e)
    {}

    constexpr auto begin() const
    {
        return pair.first;
    }
    constexpr auto end() const
    {
        return pair.second;
    }
};

constexpr auto chain(concepts::view auto&& v)
{
    return chain_wrap(begin_(PP_F(v)), end_(PP_F(v)));
}
}

template <typename I, typename E>
constexpr auto operator^(PP::view_chain_wrap<I, E> vc,
                         PP::concepts::view auto&& v)
{
    // should return a simpler end iterator but any_view is broken and
    // cannot receive two different iterators
    return PP::view::chain_wrap(
        PP::view::chain_iterator(vc.begin(),
                                 vc.end(),
                                 PP::view::begin_(PP_F(v))),
        PP::view::chain_iterator(vc.end(), vc.end(), PP::view::end_(PP_F(v))));
}

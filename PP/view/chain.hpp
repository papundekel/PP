#pragma once
#include "view.hpp"

namespace PP
{
template <typename I, typename E, typename J>
class view_chain_iterator
{
    I i;
    E e;
    J j;

public:
    constexpr view_chain_iterator(const I& i, const E& e, const J& j)
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
                      PP::concepts::iterator_ra<J>)
        {
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
                      PP::concepts::iterator_ra<J>)
        {
            auto first_sequence_diff = e - i;
            if (first_sequence_diff < offset)
            {
                i += first_sequence_diff;
                j += offset - first_sequence_diff;
            }
            else
            {
                i += offset;
            }
        }
        else
            return 0;
    }

    constexpr bool operator==(const view_chain_iterator& other) const
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

    constexpr ptrdiff_t operator-(const view_chain_iterator& other) const
    {
        if (e == other.e)
            return (i - other.i) + (j - other.j);
        else
            return 0;
    }
};

template <typename I, typename E>
class view_chain_wrap
{
    compressed_pair<I, E> pair;

public:
    constexpr view_chain_wrap(const I& i, const E& e)
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

constexpr auto view_chain(concepts::view auto&& v)
{
    return view_chain_wrap(view::begin(PP_F(v)), view::end(PP_F(v)));
}

template <typename I, typename E>
constexpr auto operator^(view_chain_wrap<I, E> vc, concepts::view auto&& v)
{
    // should return a simpler end iterator but any_view is broken and
    // cannot receive two different iterators
    return view_chain_wrap(
        view_chain_iterator(vc.begin(), vc.end(), view::begin(PP_F(v))),
        view_chain_iterator(vc.end(), vc.end(), view::end(PP_F(v))));
}
}

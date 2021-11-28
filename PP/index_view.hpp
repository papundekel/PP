#pragma once
#include <PP/utility/move.hpp>

namespace PP
{
template <typename W>
class wrap_iterator
{
    W w;

public:
    constexpr wrap_iterator(W w)
        : w(move(w))
    {}

    constexpr auto& operator*() const
    {
        return w;
    }
    constexpr auto operator->() const
    {
        return &w;
    }
    constexpr auto operator+(const auto& other) const
    {
        return wrap_iterator(w + other);
    }
};

template <typename F>
class index_view
{
    F f;

public:
    constexpr index_view(F f)
        : f(move(f))
    {}

    constexpr auto begin() const
    {}
    constexpr auto end() const
    {}
};
}

#pragma once
#include <PP/utility/forward.hpp>

namespace PP
{
template <typename C>
class push_back_iterator
{
    C* c;

public:
    constexpr push_back_iterator() noexcept
        : c(nullptr)
    {}
    constexpr push_back_iterator(C& c) noexcept
        : c(&c)
    {}

    constexpr const push_back_iterator& operator*() const noexcept
    {
        return *this;
    }
    constexpr push_back_iterator& operator++() noexcept
    {
        return *this;
    }
    constexpr push_back_iterator operator++(int) noexcept
    {
        return *this;
    }
    constexpr const push_back_iterator& operator=(auto&& value) const
    {
        c->push_back(PP_F(value));

        return *this;
    }
    constexpr bool operator==(push_back_iterator other) const noexcept
    {
        return c == other.c;
    }
};
}
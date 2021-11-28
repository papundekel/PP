#pragma once
#include <PP/compressed_pair.hpp>
#include <PP/get_type.hpp>
#include <PP/movable.hpp>
#include <PP/pointer_base.hpp>
#include <PP/size_t.hpp>

namespace PP
{
template <typename T, typename Allocator>
class pointer_allocate : public pointer_base<T>
{
    template <typename, typename>
    friend class pointer_allocate;

    compressed_pair<size_t, Allocator> count_allocator;

public:
    constexpr pointer_allocate()
        : pointer_base<T>()
        , count_allocator(0, Allocator())
    {}
    constexpr pointer_allocate(decltype(nullptr))
        : pointer_allocate()
    {}

    constexpr pointer_allocate(auto&& allocator, size_t count)
        : pointer_base<T>(count != 0 ? PP_F(allocator).allocate(count)
                                     : nullptr)
        , count_allocator(count, PP_F(allocator))
    {}

    template <detail::pointer_new_compatible<T> U, typename AllocatorOther>
    constexpr pointer_allocate(
        const pointer_allocate<U, AllocatorOther>& other) noexcept
        : pointer_base<T>(other)
        , count_allocator(other.count_allocator.first,
                          other.count_allocator.second)
    {}
    template <detail::pointer_new_compatible<T> U, typename AllocatorOther>
    constexpr pointer_allocate(
        pointer_allocate<U, AllocatorOther>&& other) noexcept
        : pointer_base<T>(move(other))
        , count_allocator(other.count_allocator.first,
                          move(other).count_allocator.second)
    {}

    template <detail::pointer_new_compatible<T> U, typename AllocatorOther>
    constexpr pointer_allocate& operator=(
        const pointer_allocate<U, AllocatorOther>& other) noexcept
    {
        pointer_base<T>::operator=(move(other));
        count_allocator = other.count_allocator;
        return *this;
    }
    template <detail::pointer_new_compatible<T> U, typename AllocatorOther>
    constexpr pointer_allocate& operator=(
        pointer_allocate<U, AllocatorOther>&& other) noexcept
    {
        pointer_base<T>::operator=(move(other));
        count_allocator = move(other).count_allocator;
        return *this;
    }

    constexpr size_t count() const noexcept
    {
        return count_allocator.first;
    }

    constexpr void deallocate()
    {
        if (this->ptr)
            count_allocator.second.deallocate(this->ptr, count());
    }

    constexpr auto& get_allocator()
    {
        return count_allocator.second;
    }
};
}

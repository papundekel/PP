#pragma once
#include "construct_at_pack.hpp"
#include "construct_pack.hpp"
#include "pack/apply_template.hpp"
#include "static_block.hpp"

namespace PP
{
constexpr inline struct nullopt_t
{
} nullopt{};

template <typename T>
class optional
{
    friend struct optional_creator;

    static_block<T, 1> block;
    bool has_value;

public:
    constexpr optional(nullopt_t) noexcept
        : block()
        , has_value(false)
    {}

    constexpr optional(const optional& other)
        : block()
        , has_value(other.has_value)
    {
        if (has_value)
            construct(*other);
    }

    constexpr optional(optional&& other)
        : block()
        , has_value(other.has_value)
    {
        if (has_value)
            construct(*move(other));
    }

    constexpr ~optional()
    {
        reset();
    }

    constexpr optional(placeholder_t, auto&&... args)
        : block()
        , has_value(true)
    {
        construct(PP_F(args)...);
    }

public:
    static constexpr auto create(auto&&... args)
    {
        return optional(placeholder, PP_F(args)...);
    }

    constexpr explicit operator bool() const noexcept
    {
        return has_value;
    }

    constexpr T& operator*() & noexcept
    {
        return *get_ptr();
    }
    constexpr T&& operator*() && noexcept
    {
        return move(*get_ptr());
    }
    constexpr const T& operator*() const& noexcept
    {
        return *get_ptr();
    }
    constexpr const T&& operator*() const&& noexcept
    {
        return move(*get_ptr());
    }

    constexpr T* operator->() noexcept
    {
        return get_ptr();
    }
    constexpr const T* operator->() const noexcept
    {
        return get_ptr();
    }

    constexpr void emplace(auto&&... args)
    {
        destroy();

        construct(PP_F(args)...);

        has_value = true;
    }

    constexpr void reset()
    {
        destroy();

        has_value = false;
    }

private:
    constexpr T* get_ptr()
    {
        return block.begin();
    }
    constexpr const T* get_ptr() const
    {
        return block.begin();
    }

    constexpr void destroy()
    {
        if (has_value)
            get_ptr()->~T();
    }

    constexpr void construct(auto&&... args)
    {
        construct_at_pack(get_ptr(), PP_F(args)...);
    }
};

PP_CIA make_optional_copy = [](auto&& arg)
{
    return optional<PP_GT(~PP_DT(arg))>::create(PP_F(arg));
};
}

#pragma once
//#include "arg_splitter.hpp"
#include "compressed_pair.hpp"
#include "containers/type_tuple.hpp"
#include "in_place_tag.hpp"
#include "placeholder.hpp"
#include "tags.hpp"
#include "utility/move.hpp"

namespace PP
{
// constexpr inline struct scoped_in_place_delimiter_t {}
// scoped_in_place_delimiter;

constexpr inline struct scoped_default_destructor_tag_t
{
} scoped_default_destructor_tag;

template <typename T, typename Destructor>
class scoped
{
    // static constexpr auto splitter = arg_splitter *
    // type<scoped_in_place_delimiter_t> * type_tuple<T, Destructor>;

    template <typename U, typename D>
    friend class scoped;

    compressed_pair<T, Destructor> pair;

public:
    // constexpr scoped(in_place_tag_t, auto&&... args)
    //	: pair(
    //		splitter(value_0, PP_F(args)...),
    //		splitter(value_1, PP_F(args)...))
    //{}

    constexpr scoped(in_place_tag_t, auto&& destructor, auto&&... args)
        : pair(T(PP_F(args)...), Destructor(PP_F(destructor)))
    {}
    constexpr scoped(scoped_default_destructor_tag_t, auto&&... args)
        : scoped(in_place_tag, Destructor(), PP_F(args)...)
    {}
    constexpr scoped(placeholder_t, auto&& value, auto&& destructor)
        : pair(PP_F(value), PP_F(destructor))
    {}

    scoped() = default;

    constexpr scoped(const scoped& other)
        : pair(other.pair.first, other.pair.second)
    {}
    template <typename U, typename D>
    constexpr scoped(const scoped<U, D>& other)
        : pair(other.pair.first, other.pair.second)
    {}
    constexpr scoped(scoped&& other)
        : pair(move(other).pair.first, move(other).pair.second)
    {}
    template <typename U, typename D>
    constexpr scoped(scoped<U, D>&& other)
        : pair(move(other).pair.first, move(other).pair.second)
    {}

    constexpr auto& get_object() noexcept
    {
        return pair.first;
    }
    constexpr auto& get_object() const noexcept
    {
        return pair.first;
    }
    constexpr auto& get_destructor() noexcept
    {
        return pair.second;
    }
    constexpr auto& get_destructor() const noexcept
    {
        return pair.second;
    }

    constexpr auto& operator[](tags::o_t) noexcept
    {
        return get_object();
    }
    constexpr auto& operator[](tags::o_t) const noexcept
    {
        return get_object();
    }
    constexpr auto& operator[](tags::d_t) noexcept
    {
        return get_destructor();
    }
    constexpr auto& operator[](tags::d_t) const noexcept
    {
        return get_destructor();
    }

private:
    constexpr void destroy()
    {
        get_destructor()(get_object());
    }

public:
    template <typename U, typename D>
    constexpr scoped& operator=(const scoped<U, D>& other)
    {
        if (this != &other)
        {
            destroy();
            pair.first = other.pair.first;
            pair.second = other.pair.second;
        }

        return *this;
    }
    template <typename U, typename D>
    constexpr scoped& operator=(scoped<U, D>&& other)
    {
        if (this != &other)
        {
            destroy();
            pair.first = move(other).pair.first;
            pair.second = move(other).pair.second;
        }
        return *this;
    }
    constexpr ~scoped()
    {
        destroy();
    }
};
scoped(auto&& v, auto&& d) -> scoped<PP_GT(~PP_DT(v)), PP_GT(~PP_DT(d))>;
}

#pragma once
#include "../add_const.hpp"
#include "../apply_partially_first.hpp"
#include "../apply_template.hpp"
#include "../construct_pack.hpp"
#include "../copy_cvref.hpp"
#include "../decay.hpp"
#include "../decompose_template.hpp"
#include "../get_value.hpp"
#include "../id.hpp"
#include "../init_type.hpp"
#include "../placeholder.hpp"
#include "../tuple/concept.hpp"
#include "../utility/move.hpp"
#include "../value_sequence.hpp"
#include "type_tuple.hpp"

namespace PP::detail
{
template <PP::size_t, typename T>
class tuple_wrap
{
    friend class tuple_helper;

    T obj;

public:
    constexpr tuple_wrap(placeholder_t, auto&& i)
        : obj(PP_F(i))
    {}
    constexpr tuple_wrap(in_place_t, auto&& i)
        : obj(PP_F(i)())
    {}
};

template <typename, typename... T>
class tuple_impl;
template <PP::size_t... I, typename... T>
class tuple_impl<value_sequence<I...>, T...> : private tuple_wrap<I, T>...
{
    friend class tuple_helper;

    static constexpr auto wrap_types = type_tuple<tuple_wrap<I, T>&...>;
    static constexpr auto types = type_tuple<T...>;

public:
    constexpr tuple_impl()
        : tuple_wrap<I, T>()...
    {}

    constexpr tuple_impl(placeholder_t,
                         auto&&... args) requires(sizeof...(args) ==
                                                  sizeof...(T))
        : tuple_wrap<I, T>(placeholder, PP_F(args))...
    {}
    constexpr tuple_impl(in_place_t,
                         auto&&... is) requires(sizeof...(is) == sizeof...(T))
        : tuple_wrap<I, T>(in_place, PP_F(is))...
    {}
    constexpr tuple_impl(auto&& t) requires requires
    {
        (tuple_wrap<I, T>(PP_F(t)[value<I>]), ...);
    } : tuple_wrap<I, T>(PP_F(t)[value<I>])...
    {}

protected:
    constexpr void assign(auto&& t)
    {
        (((tuple_wrap<I, T>&)* this = PP_F(t)[value<I>]), ...);
    }
};

template <typename... T>
using tuple_base =
    tuple_impl<decltype(value_sequence_make(PP_SIZEOF___(T))), T...>;
}

namespace PP::tuple
{
template <typename... T>
struct container
    : public detail::tuple_base<T...>
{
    using detail::tuple_base<T...>::tuple_base;

    constexpr auto&& operator[](concepts::value auto i) & noexcept;
    constexpr auto&& operator[](concepts::value auto i) const& noexcept;
    constexpr auto&& operator[](concepts::value auto i) && noexcept;
    constexpr auto&& operator[](concepts::value auto i) const&& noexcept;

    constexpr auto element(concepts::value auto i) noexcept;
    constexpr auto element(concepts::value auto i) const noexcept;

    constexpr auto& operator=(concepts::tuple auto&& t)
    {
        assign(PP_F(t));
        return *this;
    }
};

template <typename... T>
constexpr auto tuple_count_impl(const container<T...>&) noexcept
{
    return value<sizeof...(T)>;
}

PP_CIA construct = [](concepts::tuple auto&& types,
                      concepts::value auto&& in_place,
                      auto&&... args)
{
    auto t = Template<container>[PP_F(types)];

    if constexpr (PP_GV(in_place))
        return t(PP::in_place, PP_F(args)...);
    else
        return t(PP::placeholder, PP_F(args)...);
};
}

namespace PP::detail
{
PP_CIA tuple_construct_helper =
    [](auto&& f, concepts::value auto&& in_place, auto&&... args)
{
    return tuple::construct(type_tuple<PP_GT(PP_F(f)(PP_DT(args)))...>,
                            PP_F(in_place),
                            PP_F(args)...);
};
}

namespace PP::tuple
{
PP_CIA make = detail::tuple_construct_helper * decay * value_false;
PP_CIA forward = detail::tuple_construct_helper * id_copy * value_false;
PP_CIA init = detail::tuple_construct_helper * init_type * value_true;
}

namespace PP::detail
{
struct tuple_helper
{
    static constexpr auto&& get(concepts::value auto i, auto&& t) noexcept
    {
        auto& wrap = t.wrap_types[i](t);
        return copy_cvref(PP_DT(t), PP_DT(wrap.obj))(wrap.obj);
    }
    static constexpr auto element(concepts::value auto i, auto& t) noexcept
    {
        return copy_cv(PP_DT(t), t.types[i]);
    }
};
}

template <typename... T>
constexpr auto&& PP::tuple::container<T...>::operator[](
    concepts::value auto i) & noexcept
{
    return detail::tuple_helper::get(i, *this);
}

template <typename... T>
constexpr auto&& PP::tuple::container<T...>::operator[](
    concepts::value auto i) && noexcept
{
    return detail::tuple_helper::get(i, move(*this));
}

template <typename... T>
constexpr auto&& PP::tuple::container<T...>::operator[](
    concepts::value auto i) const& noexcept
{
    return detail::tuple_helper::get(i, *this);
}

template <typename... T>
constexpr auto&& PP::tuple::container<T...>::operator[](
    concepts::value auto i) const&& noexcept
{
    return detail::tuple_helper::get(i, move(*this));
}

template <typename... T>
constexpr auto PP::tuple::container<T...>::element(
    concepts::value auto i) noexcept
{
    return detail::tuple_helper::element(i, *this);
}

template <typename... T>
constexpr auto PP::tuple::container<T...>::element(
    concepts::value auto i) const noexcept
{
    return detail::tuple_helper::element(i, *this);
}

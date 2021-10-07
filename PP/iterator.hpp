#pragma once
#include "concepts/equatable.hpp"
#include "concepts/fundamental_types.hpp"
#include "concepts/non_void.hpp"
#include "concepts/same.hpp"
#include "functor.hpp"
#include "ptrdiff_t.hpp"

namespace PP::detail
{
template <typename T>
concept has_step = requires(T t)
{
    {
        t.step()
        } -> concepts::void_type;
};
template <typename T>
concept has_step_back = requires(T t)
{
    {
        t.step_back()
        } -> concepts::void_type;
};
template <typename T>
concept has_advance = requires(T t, ptrdiff_t n)
{
    {
        t.advance(n)
        } -> concepts::void_type;
};

template <typename T>
concept has_step_or_advance = has_step<T> || has_advance<T>;
template <typename T>
concept has_step_back_or_advance = has_step_back<T> || has_advance<T>;
}

constexpr auto& operator+=(PP::detail::has_step_or_advance auto& t,
                           PP::ptrdiff_t offset)
{
    if constexpr (PP::detail::has_advance<decltype(t)>)
        t.advance(offset);
    else
    {
        for (PP::ptrdiff_t i = 0; i != offset; ++i)
            t.step();
    }

    return t;
}
constexpr auto& operator-=(PP::detail::has_step_back_or_advance auto& t,
                           PP::ptrdiff_t offset)
{
    if constexpr (PP::detail::has_advance<decltype(t)>)
        t.advance(-offset);
    else
    {
        for (PP::ptrdiff_t i = 0; i != offset; ++i)
            t.step_back();
    }

    return t;
}

namespace PP::detail
{
template <typename T>
concept has_operator_advance = requires(T t, ptrdiff_t n)
{
    {
        t += n
        } -> concepts::same<T&>;
};

template <typename T>
concept has_operator_back = requires(T t, ptrdiff_t n)
{
    {
        t -= n
        } -> concepts::same<T&>;
};
}

constexpr auto operator+(PP::detail::has_operator_advance auto t,
                         PP::ptrdiff_t offset)
{
    t += offset;
    return t;
}

constexpr auto operator-(PP::detail::has_operator_back auto t,
                         PP::ptrdiff_t offset)
{
    t -= offset;
    return t;
}

constexpr auto& operator++(PP::detail::has_step_or_advance auto& t)
{
    if constexpr (PP::detail::has_advance<decltype(t)>)
        t += 1;
    else
        t.step();

    return t;
}

constexpr auto operator++(PP::detail::has_step_or_advance auto& t, int)
{
    auto x = t;
    ++t;
    return x;
}

constexpr auto& operator--(PP::detail::has_operator_back auto& t)
{
    if constexpr (PP::detail::has_advance<decltype(t)>)
        t -= 1;
    else
        t.step_back();

    return t;
}

constexpr auto operator--(PP::detail::has_operator_back auto& t, int)
{
    auto x = t;
    --t;
    return x;
}

namespace PP::concepts
{
template <typename T>
concept iterator = requires(T i)
{
    ++i;
    {
        *i
        } -> non_void;
};

template <typename T>
concept iterator_bi = requires(T i)
{
    --i;
}
&&iterator<T>;

template <typename T>
concept iterator_ra = requires(T i)
{
    i += ptrdiff_t(0);
    {
        i[ptrdiff_t(0)]
        } -> non_void;
    i - i;
}
&&iterator_bi<T>;
}

namespace PP
{
PP_CONCEPT_FUNCTOR1(iterator);
PP_CONCEPT_FUNCTOR1(iterator_bi);
PP_CONCEPT_FUNCTOR1(iterator_ra);
}

namespace PP::concepts
{
template <typename S, typename I>
concept sentinel = iterator<I> && equatable<I, S>;
}

namespace PP
{
PP_FUNCTOR(is_sentinel, concepts::type auto s, concepts::type auto i)
{
    return concepts::sentinel<PP_GT(s), PP_GT(i)>;
});

PP_FUNCTOR(iterator_base, concepts::type auto i)
{
    return PP_DT(*declval(i));
});

PP_FUNCTOR(iterator_prev, concepts::iterator_bi auto i)
{
    --i;
    return i;
});
PP_FUNCTOR(iterator_next, concepts::iterator auto i)
{
    ++i;
    return i;
});
}

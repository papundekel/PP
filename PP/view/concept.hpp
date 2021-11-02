#pragma once
#include "../apply_transform.hpp"
#include "../call.hpp"
#include "../concepts/array.hpp"
#include "../containers/tuple.hpp"
#include "../declval.hpp"
#include "../iterator.hpp"
#include "../remove_reference.hpp"
#include "../size_t.hpp"

#include <bit>

namespace PP::detail
{
template <typename T>
concept view_concept_begin_member = requires
{
    {
        declval_impl<T>().begin()
        } -> concepts::iterator;
};
template <typename T>
concept view_concept_begin_array_reference = view_concept_begin_member<T> ||
    (is_array <<= remove_reference <<= type<T>);
template <typename T>
concept view_concept_begin_any =
    view_concept_begin_array_reference<T> || requires
{
    {
        begin(declval_impl<T>())
        } -> concepts::iterator;
};

template <typename T>
concept view_concept_end_member = requires
{
    {
        declval_impl<T>().end()
        } -> concepts::non_void;
};
template <typename T>
concept view_concept_end_bounded_array_reference = view_concept_end_member<T> ||
    (is_bounded_array <<= remove_reference <<= type<T>);
template <typename T>
concept view_concept_end_any =
    view_concept_end_bounded_array_reference<T> || requires
{
    {
        end(declval_impl<T>())
        } -> concepts::non_void;
};
}

namespace PP::view
{
PP_CIA begin_ = [](detail::view_concept_begin_any auto&& v) -> decltype(auto)
{
    if constexpr (detail::view_concept_begin_member<decltype(v)>)
        return PP_F(v).begin();
    else if constexpr (detail::view_concept_begin_array_reference<decltype(v)>)
        return v + 0;
    else
        return begin(PP_F(v));
};
PP_CIA end_ = [](detail::view_concept_end_any auto&& v) -> decltype(auto)
{
    if constexpr (detail::view_concept_end_member<decltype(v)>)
        return PP_F(v).end();
    else if constexpr (detail::view_concept_end_bounded_array_reference<
                           decltype(v)>)
        return v + sizeof(v) / sizeof(*v);
    else
        return end(PP_F(v));
};
}

namespace PP::detail
{
PP_CIA view_type_begin_iterator_pure = [](concepts::type auto&& v)
{
    return PP_DT(view::begin_(declval(v)));
};
}

namespace PP
{
namespace concepts
{
template <typename T>
concept view = requires
{
    {
        ::PP::view::begin_(::PP::declval_impl<T>())
        } -> concepts::iterator;
    {
        ::PP::view::end_(::PP::declval_impl<T>())
        } -> concepts::sentinel<PP_GT(
            detail::view_type_begin_iterator_pure(PP::type<T>))>;
};
}

PP_CONCEPT_FUNCTOR1(view);
}

namespace PP::view
{
constexpr size_t count(concepts::view auto&& v)
{
    if constexpr (requires
                  {
                      PP_F(v).count();
                  })
        return PP_F(v).count();
    else
        return view::end_(PP_F(v)) - view::begin_(PP_F(v));
}

constexpr bool is_empty(concepts::view auto&& v)
{
    return view::begin_(PP_F(v)) == view::end_(PP_F(v));
}
}

namespace PP::view
{
PP_CIA type_begin_iterator = [](concepts::type auto&& v)
{
    return detail::view_type_begin_iterator_pure(v);
};
PP_CIA begin_iterator = [](concepts::view auto&& v)
{
    return type_begin_iterator(PP_DT(v));
};
PP_CIA type_end_iterator = [](concepts::type auto&& v)
{
    return PP_DT(view::end_(declval(v)));
};
PP_CIA end_iterator = [](concepts::view auto&& v)
{
    return type_end_iterator(PP_DT(v));
};

PP_CIA type_base = compose(iterator_base, type_begin_iterator);
}

namespace PP::detail
{
template <typename T>
struct initializer_list_wrapper : public std::initializer_list<T> {};
template <typename T>
constexpr auto wrap_initializer_list(const std::initializer_list<T>& l)
{
    return std::bit_cast<initializer_list_wrapper<T>>(l);
}
}

namespace PP::view
{
PP_CIA begin_end = [](concepts::view auto&& v)
{
    return tuple::make(view::begin_(PP_F(v)), view::end_(PP_F(v)));
};
}

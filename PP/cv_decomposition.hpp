#pragma once
#include <PP/concepts/pointer.hpp>
#include <PP/concepts/pointer_to_member.hpp>
#include <PP/empty.hpp>
#include <PP/extent.hpp>
#include <PP/get_cv.hpp>
#include <PP/pointer_to_member_info.hpp>
#include <PP/remove_extent.hpp>
#include <PP/remove_pointer.hpp>
#include <PP/shift_view.hpp>
#include <PP/singular_tuple.hpp>
#include <PP/tuple/make.hpp>
#include <PP/tuple/map_to_array.hpp>
#include <PP/tuple/prepend.hpp>
#include <PP/view/copy.hpp>

namespace PP
{
enum class cv_decomposition_type
{
    pointer,
    pointer_to_member,
    array_known,
    array_unknown,

    none
};

struct cv_decomposition_element
{
    cv_qualifier cv;
    cv_decomposition_type type;
    size_t extent;
};

constexpr cv_decomposition_type get_cv_decomposition_type(
    concepts::type auto&& t) noexcept
{
    if (is_pointer(t))
        return cv_decomposition_type::pointer;
    else if (is_pointer_to_member(t))
        return cv_decomposition_type::pointer_to_member;
    else if (is_bounded_array(t))
        return cv_decomposition_type::array_known;
    else if (is_unbounded_array(t))
        return cv_decomposition_type::array_unknown;
    else
        return cv_decomposition_type::none;
}

PP_CIA get_cv_decomposition_element =
    [](concepts::type auto&& t) -> cv_decomposition_element
{
    return {*get_cv_value_t(t), get_cv_decomposition_type(t), extent(t)};
};

constexpr auto shed_pointer(concepts::type auto&& t)
{
    constexpr auto T = PP_CT(t);

    if constexpr (is_pointer(T))
        return remove_pointer(T);
    else if constexpr (is_pointer_to_member(T))
        return get_pointer_to_member_member_type(T);
    else
        return remove_extent(T);
}

constexpr auto shed_pointers_helper(concepts::type auto&& t) noexcept
{
    constexpr auto T = PP_CT(t);
    constexpr auto shedded = shed_pointer(T);

    if constexpr (shedded != T)
        return !tuple::prepend(T, shed_pointers_helper(shedded));
    else
        return make_singular_tuple(T);
}

PP_CIA shed_pointers = [](concepts::type auto&& t)
{
    return shed_pointers_helper(PP_F(t));
};

constexpr inline PP::functor array_tail_value(
    []<typename T, size_t N>(PP::array<T, N> arr)
    {
    using namespace PP::literals;

    PP::array<T, N - 1> result;
    PP::view_copy(result, 1_s >> arr);
    return result;
    };

PP_CIA cv_decomposition = compose_many(array_tail_value,
                          tuple::map_to_array * type<cv_decomposition_element> *
                              get_cv_decomposition_element, 
                          shed_pointers);
}

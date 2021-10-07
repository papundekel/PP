#pragma once
#include <variant>

#include "add_pointer.hpp"
#include "alignment_of.hpp"
#include "apply_partially.hpp"
#include "compose.hpp"
#include "concepts/trivially_destructible.hpp"
#include "construct_at_pack.hpp"
#include "max_default.hpp"
#include "operators.hpp"
#include "ref_wrap.hpp"
#include "reinterpret_cast.hpp"
#include "size_of.hpp"
#include "tuple/find.hpp"
#include "tuple/map_to_array.hpp"

namespace PP
{
namespace detail
{
class visit_helper;
}

template <typename... TypeClasses>
class variant
{
    friend detail::visit_helper;

    std::variant<wrap_ref_t<TypeClasses>...> v;

public:
    constexpr variant(placeholder_t, auto&& x) noexcept
        : v(PP_F(x))
    {}

    constexpr bool holds_alternative(concepts::type auto t) const noexcept
    {
        return std::holds_alternative<wrap_ref_t<PP_GT(t)>>(v);
    }
};

namespace detail
{
template <typename... T>
class variant2
{
    friend detail::visit_helper;

    static constexpr auto types = type_tuple<T...>;
    static constexpr auto max =
        (id_copy | der | max_default |
         tuple_map_make_array)(partial_tag, value_1, types);

    static constexpr auto type_eql = functor(
        [](auto t, auto u)
        {
            return value<PP_COPY_TYPE(t) == PP_COPY_TYPE(u)>;
        });

    size_t index;
    alignas(max(alignment_of)) char buffer[max(size_of)];

    static constexpr size_t get_type_index(concepts::type auto t) noexcept
    {
        return tuple::find(type_eql * t, types);
    }

public:
    constexpr variant2(concepts::type auto t, auto&&... args)
        : index(0)
        , buffer()
    {
        auto i = get_type_index(t);

        static_assert(PP_GV(i) != sizeof...(T), "type is not in this variant");

        index = *i;

        construct_at_pack(reinterpret__cast(add_pointer <<= types[i], buffer),
                          PP_F(args)...);
    }

    constexpr bool holds_alternative(concepts::type auto t) const noexcept
    {
        return *get_type_index(t) == index;
    }

    constexpr ~variant2()
    {}

    // clang-format off
		constexpr ~variant2()
			requires (concepts::trivially_destructible<T> && ...)
		= default;
    // clang-format on
};
}

namespace detail
{
struct visit_helper
{
    template <typename V, typename R, typename... T>
    using functor = R (*)(V, T...);

    static PP_FUNCTOR(visit, auto&& visitor, auto&&... variants)
        -> decltype(auto)
    {
        return std::visit(compose(PP_REF_WRAP(visitor), unwrap_ref),
                          PP_F(variants).v...);
    });

    static PP_FUNCTOR(visit2, auto&& visitor, auto&&... variants)
        -> decltype(auto)
    {
        auto table_tuple =
            PP::applier(
                [](auto... types)
                {
                    return
                        [](auto&& variant, auto&... buffers) -> decltype(auto)
                    {
                        return PP_F(variant)(
                            reinterpret__cast(PP_COPY_TYPE(types), buffers)...);
                    };
                }) +
            tuple_cartesian_product_pack(variants.types...);

        // tuple_map_make_array(, )

        // Template<functor>[PP_DT(visitor) += type_void +=
        //					  make_iterate_tuple(PP_SIZEOF___(variants),
        //										 type<char&>)]
    });
};
}

PP_CIA visit = detail::visit_helper::visit;

namespace detail
{
PP_CIA visit2 = detail::visit_helper::visit2;
}
}

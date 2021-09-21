#pragma once
#include "noop.hpp"
#include "operators.hpp"
#include "view/zip_if.hpp"

namespace PP
{
enum class subsequence_type
{
    proper,
    equal,
    none,
};

// struct subsequence_type
//{
//	int x;
//	static constexpr subsequence_type proper{0};
//	static constexpr subsequence_type equal{1};
//	static constexpr subsequence_type none{2};
//	constexpr operator std::partial_ordering() const noexcept
//	{
//		if (*this == proper)
//			return
//	}
//};

PP_FUNCTOR(view_subsequence_if,
           auto&& comparer,
           concepts::view auto&& sub,
           concepts::view auto&& full)
{
    bool may_be_proper = false;

    auto [sub_end, full_end] = view_zip_if_pack(
        [&may_be_proper, &comparer](auto&& sub_element, auto&& full_element)
        {
            auto cond = PP_F(comparer)(PP_F(sub_element), PP_F(full_element));

            if (!cond)
                may_be_proper = true;

            return make_tuple(cond, make_array(cond, true));
        },
        noop,
        PP_F(sub),
        PP_F(full));

    if (sub_end == view::end(PP_F(sub)) && full_end == view::end(PP_F(full)))
    {
        if (may_be_proper)
            return subsequence_type::proper;
        else
            return subsequence_type::equal;
    }
    else
        return subsequence_type::none;
});

PP_CIA view_subsequence = view_subsequence_if * eql;
}

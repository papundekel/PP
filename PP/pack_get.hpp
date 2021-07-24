#pragma once
#include "functor.hpp"
#include "get_value.hpp"

namespace PP
{
namespace detail
{
constexpr decltype(auto) pack_get_implementation(concepts::value auto i,
                                                 auto&& first,
                                                 auto&&... pack) noexcept
{
	if constexpr (*PP_CV(i) == 0)
		return PP_F(first);
	else
		return pack_get_implementation(i - value_1, PP_F(pack)...);
}
}

PP_FUNCTOR(pack_get, concepts::value auto i, auto&&... pack) -> decltype(auto)
{
	return detail::pack_get_implementation(i, PP_F(pack)...);
});
}

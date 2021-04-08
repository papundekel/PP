#pragma once
#include <variant>

#include "functional/compose.hpp"
#include "ref_wrap.hpp"

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
			: v(PP_FORWARD(x))
		{}

		constexpr bool holds_alternative(concepts::type auto t) const noexcept
		{
			return std::holds_alternative<wrap_ref_t<PP_GET_TYPE(t)>>(v);
		}
	};

	namespace detail
	{
		struct visit_helper
		{
			static PP_FUNCTOR(visit, auto&& visitor, auto&&... variants) -> decltype(auto)
			{
				return std::visit(compose(PP_REF_WRAP(visitor), unwrap_ref), PP_FORWARD(variants).v...);
			});
		};
	}

	constexpr inline auto visit = detail::visit_helper::visit;
}

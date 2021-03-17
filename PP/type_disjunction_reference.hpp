#pragma once
#include <variant>

#include "add_cv.hpp"
#include "forward_wrap.hpp"
#include "get_type.hpp"
#include "ref_wrap.hpp"

namespace PP
{
	template <typename... TypeClasses>
	class type_disjunction_reference
	{
		std::variant<ref_wrap<const TypeClasses>...> v;

	public:
		type_disjunction_reference(const type_disjunction_reference&) = default;
		
		constexpr type_disjunction_reference(const auto& t) noexcept
			: v(ref_wrap(t))
		{}

		constexpr bool holds_alternative(concepts::type auto t) const noexcept
		{
			return std::holds_alternative<PP_GET_TYPE(Template<ref_wrap>(t + add_const_tag))>(v);
		}

		constexpr decltype(auto) visit(auto&& f) const
		{
			return std::visit([f_wrap = PP_FORWARD_WRAP(f)]
				<typename T>
				(ref_wrap<T> wrap) -> decltype(auto)
				{
					return f_wrap.unwrap()(wrap.get());
				}, v);
		}
	};
}

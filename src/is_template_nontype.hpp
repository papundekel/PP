#pragma once
#include "val.hpp"

namespace dis_template_nontype
{
	template <template <auto...> typename T>
	struct x
	{
	private:
		template <typename U>
		struct y : val<false> {};
		template <auto... U>
		struct y<T<U...>> : val<true> {};
	public:
		template <typename U>
		static constexpr auto z = y<untype<U>>::v;
	};
}

template <template <auto...> typename T, typename U>
constexpr auto is_template_nontype(U) { return dis_template_nontype::x<T>::template z<U>; }
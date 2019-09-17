#pragma once
#include "val.hpp"
#include "type.hpp"

namespace dis_template
{
	template <template <typename...> typename T>
	struct x
	{
	private:
		template <typename U>
		struct y : val<false> {};
		template <typename... U>
		struct y<T<U...>> : val<true> {};
	public:
		template <typename U>
		static constexpr auto z = y<untype<U>>::v;
	};
}

template <template <typename...> typename T, typename U>
constexpr auto is_template(U) { return dis_template::x<T>::template z<U>; }
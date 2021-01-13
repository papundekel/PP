#pragma once

namespace PP
{
	template <typename T>
	struct type_t
	{
		using type = T;

		constexpr auto operator->() const noexcept;

		static constexpr char arbitrary_concept_tag_type_t = {};
	};
	template <typename T>
	constexpr inline type_t<T> type_v = {};

	template <typename T, typename U>
	constexpr auto operator==(type_t<T>, type_t<U>) noexcept
	{
		return false;
	}
	template <typename T>
	constexpr auto operator==(type_t<T>, type_t<T>) noexcept
	{
		return true;
	}

	constexpr auto get(auto i, type_t<auto> t) noexcept
	requires (*decltype(i){} == 0)
	{
		return t;
	}
	constexpr std::size_t size_implementation(auto t) noexcept
	requires requires { decltype(t)::type::arbitrary_concept_tag_type_t; }
	{
		return 1;
	}

	#define PP_TYPE_UNSAFE(x) typename decltype(x)::type
	#define PP_DECLTYPE(x) (::PP::type_v<decltype(x)>)
}

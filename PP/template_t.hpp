#pragma once

namespace PP
{
	template <template <typename...> typename Template>
	struct template_t
	{
		constexpr auto operator[](auto&& types) const noexcept;
	};
	template <template <typename...> typename Template>
	constexpr inline template_t<Template> template_v = {};

	template <template <typename...> typename T, template <typename...> typename U>
	constexpr auto operator==(template_t<T>, template_t<U>) noexcept
	{
		return false;
	}
	template <template <typename...> typename T>
	constexpr auto operator==(template_t<T>, template_t<T>) noexcept
	{
		return true;
	}
}

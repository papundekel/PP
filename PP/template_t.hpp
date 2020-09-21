#pragma once

namespace PP
{
	template <template <typename...> typename Template>
	struct template_t {};

	template <template <typename...> typename Template>
	constexpr inline auto template_v = template_t<Template>{};
}

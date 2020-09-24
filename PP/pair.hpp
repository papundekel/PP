#include <utility>
#include "value_t.hpp"
#include "get_value.hpp"

namespace PP::detail
{
	template <typename T>
	struct is_std_pair_helper : public value_t<false> {};
	template <typename T, typename U>
	struct is_std_pair_helper<std::pair<T, U>> : public value_t<true> {};

	template <typename T>
	concept is_std_pair = get_value<is_std_pair_helper<std::remove_cvref_t<T>>>();
}

namespace std
{
	template <std::size_t I, PP::detail::is_std_pair T>
	constexpr decltype(auto) get(PP::value_t<I>, T&& p)
	{
		return std::get<I>(std::forward<T>(p));
	}
}

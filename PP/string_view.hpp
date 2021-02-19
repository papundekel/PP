#pragma once
#include "size_t.hpp"

namespace PP
{
	template <typename CharT>
	class basic_string_view
	{
		const CharT* begin_;
		const CharT* end_;

	public:
		constexpr basic_string_view(const CharT* begin, const CharT* end) noexcept
			: begin_(begin)
			, end_(end)
		{}
		template <size_t N>
		constexpr basic_string_view(const CharT(&arr)[N]) noexcept
			: basic_string_view(arr, arr + N - 1)
		{}

		constexpr auto begin() const noexcept
		{
			return begin_;
		}
		constexpr auto end() const noexcept
		{
			return end_;
		}

		constexpr auto substr(size_t index) const noexcept
		{
			return basic_string_view(begin_ + index, end_);
		}
	};

	using string_view = basic_string_view<char>;

	inline namespace literals
	{
		constexpr auto operator""_sv(const char* s, size_t l)
		{
			return string_view(s, s + l);
		}
	}
}

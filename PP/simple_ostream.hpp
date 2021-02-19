#pragma once
#include <iosfwd>

#include "any_view.hpp"
#include "array.hpp"
#include "to_chars.hpp"

namespace PP
{
	class simple_ostream
	{
	public:
		constexpr virtual void write(any_view<iterator_category::forward, const char&> view) noexcept = 0;
		template <size_t N>
		constexpr void write(const char(&arr)[N]) noexcept
		{
			write(make_any_view(arr, arr + N - 1));
		}
		void virtual write_to_ostream(std::ostream&) noexcept = 0;

		constexpr void write(size_t number) noexcept
		{
			array<char, 32> buffer;
			auto end = to_chars(buffer, number);
			write(make_any_view(view_begin(buffer), end));
		}
	};
}

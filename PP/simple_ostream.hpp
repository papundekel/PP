#pragma once
#include <iosfwd>

#include "any_iterator.hpp"
#include "array.hpp"
#include "to_chars.hpp"

namespace PP
{
	class simple_ostream
	{
	public:
		constexpr virtual void write(any_view_ra<const char&> view) noexcept = 0;
		void virtual write_to_ostream(std::ostream&) noexcept = 0;

		constexpr void write(size_t number) noexcept
		{
			array<char, 32> buffer;
			auto count = to_chars(buffer, number);
			write(std::string_view(buffer.data(), count));
		}
	};
}

#pragma once
#include <ostream>
#include <string_view>
#include <array>
#include "to_chars.hpp"

namespace PP
{
	class simple_ostream
	{
	public:
		constexpr virtual void write(std::string_view) noexcept = 0;
		void virtual write_to_ostream(std::ostream&) noexcept = 0;

		constexpr void write(std::size_t number) noexcept
		{
			std::array<char, 32> buffer;
			auto count = to_chars(buffer.data(), buffer.data() + buffer.size(), number);
			write(std::string_view(buffer.data(), count));
		}
	};
}

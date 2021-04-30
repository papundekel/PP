#pragma once
#include "simple_ostream.hpp"

namespace PP
{
	class std_ostream final : public simple_ostream
	{
		std::ostream& out;

	public:
		constexpr std_ostream(std::ostream& out)
			: out(out)
		{}

		constexpr void write(any_view<iterator_category::forward, char>
								 view) noexcept override final
		{
			for (char c : view)
				out << c;
		}
	};
}

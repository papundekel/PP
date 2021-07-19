#pragma once
#include <ostream>

#include "ostream.hpp"
#include "view.hpp"

namespace PP
{
	template <template <typename> typename Buffer>
	class basic_ostream final : public ostream
	{
		Buffer<char> buffer;

	public:
		constexpr void write(
			any_view<iterator_category::fw, char> view) noexcept override final
		{
			for (char c : view)
				buffer.push_back(c);
		}
	};
}

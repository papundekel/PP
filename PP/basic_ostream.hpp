#pragma once
#include <ostream>

#include "simple_ostream.hpp"

namespace PP
{
	template <template <typename> typename Buffer>
	class basic_ostream final : public simple_ostream
	{
		Buffer<char> buffer;

	public:
		constexpr void write(any_view_ra<const char&> view) noexcept override final
		{
			for (auto& c : view)
				buffer.push_back(c);
		}
		void write_to_ostream(std::ostream& out) noexcept override final
		{
			out.write(view_begin(buffer), view_count(buffer));
			buffer.clear();
		}
	};
}

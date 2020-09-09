#pragma once
#include "simple_ostream.hpp"

namespace PP
{
	template <template <typename> typename Buffer>
	class basic_ostream final : public simple_ostream
	{
		Buffer<char> buffer;

	public:
		constexpr void write(std::string_view s) noexcept override final
		{
			for (char c : s)
				buffer.push_back(c);
		}
		void write_to_ostream(std::ostream& out) noexcept override final
		{
			out.write(buffer.begin(), buffer.count());
			buffer.clear();
		}
	};
}

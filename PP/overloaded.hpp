#pragma once

namespace PP
{
	template<class... Ts>
	struct overloaded : public Ts...
	{
		using Ts::operator()...;
	};
}

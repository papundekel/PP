#pragma once

namespace PP
{
	#define PP_FORWARD(x) static_cast<decltype(x)&&>(x)
}

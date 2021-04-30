#pragma once

#define PP_FORWARD(x) static_cast<decltype(x)&&>(x)

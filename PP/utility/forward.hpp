#pragma once

#define PP_F(x) static_cast<decltype(x)&&>(x)
#define PP_FL(x) x = PP_F(x)

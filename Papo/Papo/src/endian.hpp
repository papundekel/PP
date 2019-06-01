#pragma once

/*constexpr bool _is_little_endian()
{
	union {
		int i;
		char c[4];
	} x = { 0x01020304 };
	
	return x.c[0] != 1;
}

constexpr bool is_little_endian = _is_little_endian();*/
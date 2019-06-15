#pragma once
#include <cstring>
#include "min.hpp"

template <typename Src, typename Dest>
inline Dest* mem_cpy(const Src* src, Dest* dest, size_t count)
{
	return reinterpret_cast<Dest*>(memcpy(dest, src, count * sizeof(Src)));
}

template <typename Src, size_t src_size, typename Dest>
inline Dest* mem_cpy(const Src(&src)[src_size], Dest* dest)
{
	return mem_cpy(dest, src, src_size);
}
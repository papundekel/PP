#pragma once
#include <cstring>
template <typename Dest, typename Src>
inline Dest* mem_cpy(Dest* dest, const Src* src, size_t count)
{
	return reinterpret_cast<Dest*>(memcpy(dest, src, count * sizeof(Src)));
}

template <typename Dest, typename Src, size_t s>
inline Dest* mem_cpy(Dest* dest, const Src(&src)[s])
{
	return mem_copy(dest, src, sizeof(src));
}
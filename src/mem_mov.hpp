#include <cstring>

template <typename Src, typename Dest>
inline Dest* mem_mov(const Src* src, Dest* dest, size_t count)
{
	return reinterpret_cast<Dest*>(memmove(dest, src, count * sizeof(Src)));
}

template <typename Src, size_t src_size, typename Dest>
inline Dest* mem_mov(const Src(&src)[src_size], Dest* dest)
{
	return mem_mov(src, dest, src_size);
}
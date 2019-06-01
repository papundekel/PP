#pragma once

template <typename it>
concept iterator = requires(it i)
{
	*i;
	++i;
	i++;
};

template <iterator it>
concept iterator_bidirectional = requires(it i)
{
	--i;
	i--;
};

template <iterator_bidirectional it>
concept iterator_random_access = requires(it i, it j, size_t diff)
{
	i[diff];
	i + diff;
	i - j;
};

template <typename C, iterator it>
concept container = requires(C c)
{
	{ c.begin() } -> it;
	{ c.end() } -> it;
};
#pragma once
template <typename it>
bool is_sorted(it begin, it end)
{
	for (auto next = begin; ++next != end; begin = next)
		if (*begin > * next)
			return false;
	return true;
}
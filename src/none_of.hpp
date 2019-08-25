#pragma once
template <typename it, typename test>
bool none_of(it begin, it end, test t)
{
	return find_if(begin, end, t) == end;
}
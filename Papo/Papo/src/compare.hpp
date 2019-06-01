#pragma once

template <typename T, typename U>
bool operator>=(const T& left, const T& right)
{
	return !(right < left);
}
template <typename T, typename U>
bool operator>(const T& left, const T& right)
{
	return right < left;
}
template <typename T, typename U>
bool operator<=(const T& left, const T& right)
{
	return !(left > right);
}
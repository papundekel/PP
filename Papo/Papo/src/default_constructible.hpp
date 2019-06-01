#pragma once
template <typename T>
concept default_constructible = requires
{
	T();
};
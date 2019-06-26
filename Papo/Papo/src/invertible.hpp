#pragma once

template <typename T>
concept invertible = requires(T t)
{
	{ -t } -> T;
};
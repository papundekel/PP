#pragma once

template <typename T>
concept invertible_c = requires(T t)
{
	{ -t } -> T;
};
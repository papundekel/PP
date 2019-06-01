#pragma once
#include "void_t.hpp"
#include "enable_if.hpp"
#include "is_same.hpp"
#include "declval.hpp"
#include "is_pointer.hpp"
#include "remove_reference.hpp"
#include "is_convertible.hpp"

template <typename T, typename = void_t<>>
constexpr bool is_iterator = false;

template <typename T>
constexpr bool is_iterator<T,void_t<enable_if<
	is_same<T, remove_reference<decltype(++declval<T&>())>> &&
	is_convertible<decltype(declval<T>() == declval<T>()), bool> &&
	is_convertible<decltype(declval<T>() != declval<T>()), bool>>,
	decltype(*declval<T>())>>
= true;

template <typename it>
enable_if<is_iterator<it>,
it> operator++(it& i, int)
{
	auto temp = i;
	++i;
	return temp;
}
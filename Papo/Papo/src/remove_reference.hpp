#pragma once

template <typename T> struct _remove_reference		{ using type = T; };
template <typename T> struct _remove_reference<T&>	{ using type = T; };
template <typename T> struct _remove_reference<T&&> { using type = T; };
template <typename T>  using  remove_reference = typename _remove_reference<T>::type;
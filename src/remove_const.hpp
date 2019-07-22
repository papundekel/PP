#pragma once

template <typename T> struct _remove_const			{ using type = T; };
template <typename T> struct _remove_const<const T> { using type = T; };
template <typename T>  using  remove_const = typename _remove_const<T>::type;
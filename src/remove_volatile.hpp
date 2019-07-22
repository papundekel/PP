#pragma once

template <typename T> struct _remove_volatile			  { using type = T; };
template <typename T> struct _remove_volatile<volatile T> { using type = T; };
template <typename T>  using  remove_volatile = typename _remove_volatile<T>::type;
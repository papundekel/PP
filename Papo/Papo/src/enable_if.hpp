#pragma once
template <bool test, typename T = void> struct _enable_if {};
template <			 typename T>		struct _enable_if<true, T> { using type = T; };
template <bool test, typename T = void>  using  enable_if = typename _enable_if<test, T>::type;
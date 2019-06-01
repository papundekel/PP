#pragma once

template <bool test, typename T1, typename T2> struct _conditional				  { using type = T1; };
template <			 typename T1, typename T2> struct _conditional<false, T1, T2> { using type = T2; };
template <bool test, typename T1, typename T2>  using  conditional = typename _conditional<test, T1, T2>::type;
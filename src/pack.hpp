#pragma once
#include "type_t.hpp"
#include "conditional.hpp"
#include "value_t.hpp"

template <typename... T>
struct pack
{
	static constexpr auto size = 0;
	
	template <size_t N>
	using get = pack<>;

	#define constant(name, value)	template <template <typename> typename F>\
									static constexpr auto name = value
	constant(find, 0ull);
	constant(contains, false);
	constant(all, true);
	constant(count, 0ull);
	#undef constant

	template <typename... V>
	using append = pack<V...>;
	template <typename... V>
	using prepend = pack<V...>;
	template <template <typename> typename F>
	using transform = pack<>;
	template <size_t N>
	using first_n = pack<>;
};

template <typename T, typename... U>
struct pack<T, U...>
{
	static constexpr auto size = 1 + sizeof...(U);

private:
	template <size_t N>
	using get_helper = pack<U...>::template get<N - 1>;
public:
	template <size_t N>
	using get = conditional<N == 0, T, get_helper<N>>;

	template <template <typename> typename F>
	static constexpr auto find = F<T>::v ? 0 : 1 + pack<U...>::template find<F>;

	#define fold_exp(name, bin_op)	template <template <typename> typename F>\
									static constexpr auto name = F<T>::v bin_op (F<U>::v bin_op ...)
	fold_exp(contains, ||);
	fold_exp(all, &&);
	fold_exp(count, +);
	#undef fold_exp

private:
	template <typename... V>
	struct append_s : type_t<pack<T, U..., V...>> {};
	template <typename... V>
	struct append_s<pack<V...>> : type_t<pack<T, U..., V...>> {};
	template <typename... V>
	struct prepend_s : type_t<pack<V..., T, U...>> {};
	template <typename... V>
	struct prepend_s<pack<V...>> : type_t<pack<V..., T, U...>> {};
public:
	template <typename... V>
	using append = append_s<V...>::t;
	template <typename... V>
	using prepend = prepend_s<V...>::t;
	
	template <template <typename> typename F>
	using transform = pack<F<T>, F<U>...>;

private:
	template <size_t N>
	using first_n_helper = pack<U...>::template first_n<N - 1>::template prepend<T>;
public:
	template <size_t N>
	using first_n = conditional<N == 0, pack<>, first_n_helper<N>>;
};
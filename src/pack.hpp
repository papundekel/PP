#pragma once
#include "type_t.hpp"
#include "conditional.hpp"
#include "value_t.hpp"

template <typename... T>
struct pack
{
	static constexpr auto count = 0;
	template <size_t N>
	using get = pack<>;
	template <template <typename> typename F>
	static constexpr size_t find = 0;
	template <template <typename> typename F>
	static constexpr auto contains = false;
	template <template <typename> typename F>
	static constexpr auto all = true;
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
	static constexpr auto count = 1 + sizeof...(U);

private:
	template <size_t N>
	using get_helper = pack<U...>::template get<N - 1>;
public:
	template <size_t N>
	using get = conditional<N == 0, T, get_helper<N>>;

	template <template <typename> typename F>
	static constexpr auto find = F<T>::v ? 0 : 1 + pack<U...>::template find<F>;

	template <template <typename> typename F>
	static constexpr auto contains = F<T>::v || (F<U>::v || ...);

	template <template <typename> typename F>
	static constexpr auto all = F<T>::v && (F<U>::v && ...);

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
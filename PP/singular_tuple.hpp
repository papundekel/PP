#pragma once
#include "decompose_template.hpp"
#include "utility/forward.hpp"
#include "get_type.hpp"
#include "get_value.hpp"

namespace PP
{
	template <typename T>
	class singular_tuple
	{
	public:
		T obj;

		constexpr singular_tuple(auto&& obj)
			: obj(PP_FORWARD(obj))
		{}

		constexpr auto tuple_count() const noexcept
		{
			return value_1;
		}
		constexpr auto element(concepts::value auto i) const noexcept
		{
			return type<T>;
		}
		constexpr decltype(auto) operator[](concepts::value auto i) & noexcept;
		constexpr decltype(auto) operator[](concepts::value auto i) const& noexcept;
		constexpr decltype(auto) operator[](concepts::value auto i) && noexcept;
		constexpr decltype(auto) operator[](concepts::value auto i) const&& noexcept;
	};
	template <typename T>
	singular_tuple(T)->singular_tuple<T>;

	namespace concepts
	{
		template <typename T>
		concept PPsingular_tuple = PP::type<T>->Template == Template<PP::singular_tuple>;
	}

	constexpr auto& get(concepts::value auto i, concepts::PPsingular_tuple auto& t) noexcept
	requires(*PP_COPY_VALUE(i) == 0)
	{
		return t.obj;
	}
	constexpr auto&& get(concepts::value auto i, concepts::PPsingular_tuple auto&& t) noexcept
	requires(*PP_COPY_VALUE(i) == 0)
	{
		return PP_FORWARD(t.obj);
	}

	template <typename T>
	constexpr decltype(auto) singular_tuple<T>::operator[](concepts::value auto i) & noexcept
	{
		return get(i, *this);
	}
	template <typename T>
	constexpr decltype(auto) singular_tuple<T>::operator[](concepts::value auto i) const& noexcept
	{
		return get(i, *this);
	}
	template <typename T>
	constexpr decltype(auto) singular_tuple<T>::operator[](concepts::value auto i) && noexcept
	{
		return get(i, move(*this));
	}
	template <typename T>
	constexpr decltype(auto) singular_tuple<T>::operator[](concepts::value auto i) const&& noexcept
	{
		return get(i, move(*this));
	}

	constexpr auto make_singular_tuple(auto&& x)
	{
		return singular_tuple<PP_GET_TYPE(~PP_DECLTYPE(x))>(PP_FORWARD(x));
	}
	constexpr auto forward_as_singular_tuple(auto&& x) noexcept
	{
		return singular_tuple<decltype(x)>(PP_FORWARD(x));
	}
}

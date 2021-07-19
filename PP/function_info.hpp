#pragma once
#include "cv_qualifier.hpp"
#include "get_type.hpp"
#include "ref_qualifier.hpp"
#include "type_tuple.hpp"

namespace PP
{
	template <typename R, typename... P>
	class function_info
	{
	public:
		[[no_unique_address]] type_t<R> return_type;
		[[no_unique_address]] type_tuple_t<P...> parameter_types;
		bool Noexcept;
		cv_qualifier cv;
		ref_qualifier ref;

	private:
		constexpr function_info(cv_qualifier cv,
		                        ref_qualifier ref,
		                        bool Noexcept) noexcept
			: Noexcept(Noexcept)
			, cv(cv)
			, ref(ref)
		{}

	public:
		constexpr function_info(const function_info& fi) noexcept
			: function_info(fi.cv, fi.ref, fi.Noexcept)
		{}

		constexpr function_info(type_t<R(P...)>) noexcept
			: function_info(cv_qualifier::none, ref_qualifier::none, false)
		{}
		constexpr function_info(type_t<R(P...) const>) noexcept
			: function_info(cv_qualifier::Const, ref_qualifier::none, false)
		{}
		constexpr function_info(type_t<R(P...) volatile>) noexcept
			: function_info(cv_qualifier::Volatile, ref_qualifier::none, false)
		{}
		constexpr function_info(type_t<R(P...) const volatile>) noexcept
			: function_info(cv_qualifier::const_volatile,
		                    ref_qualifier::none,
		                    false)
		{}

		constexpr function_info(type_t<R(P...) &>) noexcept
			: function_info(cv_qualifier::none, ref_qualifier::lvalue, false)
		{}
		constexpr function_info(type_t<R(P...) const&>) noexcept
			: function_info(cv_qualifier::Const, ref_qualifier::lvalue, false)
		{}
		constexpr function_info(type_t<R(P...) volatile&>) noexcept
			: function_info(cv_qualifier::Volatile,
		                    ref_qualifier::lvalue,
		                    false)
		{}
		constexpr function_info(type_t<R(P...) const volatile&>) noexcept
			: function_info(cv_qualifier::const_volatile,
		                    ref_qualifier::lvalue,
		                    false)
		{}

		constexpr function_info(type_t<R(P...) &&>) noexcept
			: function_info(cv_qualifier::none, ref_qualifier::rvalue, false)
		{}
		constexpr function_info(type_t<R(P...) const&&>) noexcept
			: function_info(cv_qualifier::Const, ref_qualifier::rvalue, false)
		{}
		constexpr function_info(type_t<R(P...) volatile&&>) noexcept
			: function_info(cv_qualifier::Volatile,
		                    ref_qualifier::rvalue,
		                    false)
		{}
		constexpr function_info(type_t<R(P...) const volatile&&>) noexcept
			: function_info(cv_qualifier::const_volatile,
		                    ref_qualifier::rvalue,
		                    false)
		{}

		constexpr function_info(type_t<R(P...) noexcept>) noexcept
			: function_info(cv_qualifier::none, ref_qualifier::none, true)
		{}
		constexpr function_info(type_t<R(P...) const noexcept>) noexcept
			: function_info(cv_qualifier::Const, ref_qualifier::none, true)
		{}
		constexpr function_info(type_t<R(P...) volatile noexcept>) noexcept
			: function_info(cv_qualifier::Volatile, ref_qualifier::none, true)
		{}
		constexpr function_info(
			type_t<R(P...) const volatile noexcept>) noexcept
			: function_info(cv_qualifier::const_volatile,
		                    ref_qualifier::none,
		                    true)
		{}

		constexpr function_info(type_t<R(P...) & noexcept>) noexcept
			: function_info(cv_qualifier::none, ref_qualifier::lvalue, true)
		{}
		constexpr function_info(type_t<R(P...) const& noexcept>) noexcept
			: function_info(cv_qualifier::Const, ref_qualifier::lvalue, true)
		{}
		constexpr function_info(type_t<R(P...) volatile& noexcept>) noexcept
			: function_info(cv_qualifier::Volatile, ref_qualifier::lvalue, true)
		{}
		constexpr function_info(
			type_t<R(P...) const volatile& noexcept>) noexcept
			: function_info(cv_qualifier::const_volatile,
		                    ref_qualifier::lvalue,
		                    true)
		{}

		constexpr function_info(type_t<R(P...) && noexcept>) noexcept
			: function_info(cv_qualifier::none, ref_qualifier::rvalue, true)
		{}
		constexpr function_info(type_t<R(P...) const&& noexcept>) noexcept
			: function_info(cv_qualifier::Const, ref_qualifier::rvalue, true)
		{}
		constexpr function_info(type_t<R(P...) volatile&& noexcept>) noexcept
			: function_info(cv_qualifier::Volatile, ref_qualifier::rvalue, true)
		{}
		constexpr function_info(
			type_t<R(P...) const volatile&& noexcept>) noexcept
			: function_info(cv_qualifier::const_volatile,
		                    ref_qualifier::rvalue,
		                    true)
		{}

		template <typename T>
		constexpr function_info(type_t<T>) noexcept
			: function_info(cv_qualifier::none, ref_qualifier::none, false)
		{}
	};
	template <typename T>
	function_info(type_t<T>) -> function_info<void>;

	constexpr inline auto get_function_info = functor(
												  [](auto t)
												  {
													  return function_info(t);
												  }) |
	                                          to_type_t;
}

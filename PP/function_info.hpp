#pragma once
#include "cv_qualifier.hpp"
#include "ref_qualifier.hpp"
#include "type_t.hpp"
#include "type_tuple.hpp"

namespace PP
{
	template <typename R, typename... P>
	class function_info
	{
	public:
		cv_qualifier cv;
		ref_qualifier ref;
		bool Noexcept;
		[[no_unique_address]] type_t<R> return_type;
		[[no_unique_address]] type_tuple<P...> parameter_types;

	private:
		constexpr function_info(cv_qualifier cv, ref_qualifier ref, bool Noexcept) noexcept
			: cv(cv)
			, ref(ref)
			, Noexcept(Noexcept)
		{}

	public:
		constexpr function_info(type_t<R(P...) >) noexcept : function_info(cv_qualifier::none, ref_qualifier::none, false) {}
		constexpr function_info(type_t<R(P...) const>) noexcept : function_info(cv_qualifier::Const, ref_qualifier::none, false) {}
		constexpr function_info(type_t<R(P...) volatile>) noexcept : function_info(cv_qualifier::Volatile, ref_qualifier::none, false) {}
		constexpr function_info(type_t<R(P...) const volatile>) noexcept : function_info(cv_qualifier::const_volatile, ref_qualifier::none, false) {}

		constexpr function_info(type_t<R(P...) &>) noexcept : function_info(cv_qualifier::none, ref_qualifier::lvalue, false) {}
		constexpr function_info(type_t<R(P...) const&>) noexcept : function_info(cv_qualifier::Const, ref_qualifier::lvalue, false) {}
		constexpr function_info(type_t<R(P...) volatile&>) noexcept : function_info(cv_qualifier::Volatile, ref_qualifier::lvalue, false) {}
		constexpr function_info(type_t<R(P...) const volatile&>) noexcept : function_info(cv_qualifier::const_volatile, ref_qualifier::lvalue, false) {}

		constexpr function_info(type_t<R(P...) &&>) noexcept : function_info(cv_qualifier::none, ref_qualifier::rvalue, false) {}
		constexpr function_info(type_t<R(P...) const&&>) noexcept : function_info(cv_qualifier::Const, ref_qualifier::rvalue, false) {}
		constexpr function_info(type_t<R(P...) volatile&&>) noexcept : function_info(cv_qualifier::Volatile, ref_qualifier::rvalue, false) {}
		constexpr function_info(type_t<R(P...) const volatile&&>) noexcept : function_info(cv_qualifier::const_volatile, ref_qualifier::rvalue, false) {}


		constexpr function_info(type_t<R(P...) noexcept>) noexcept : function_info(cv_qualifier::none, ref_qualifier::none, true) {}
		constexpr function_info(type_t<R(P...) const noexcept>) noexcept : function_info(cv_qualifier::Const, ref_qualifier::none, true) {}
		constexpr function_info(type_t<R(P...) volatile noexcept>) noexcept : function_info(cv_qualifier::Volatile, ref_qualifier::none, true) {}
		constexpr function_info(type_t<R(P...) const volatile noexcept>) noexcept : function_info(cv_qualifier::const_volatile, ref_qualifier::none, true) {}

		constexpr function_info(type_t<R(P...) & noexcept>) noexcept : function_info(cv_qualifier::none, ref_qualifier::lvalue, true) {}
		constexpr function_info(type_t<R(P...) const& noexcept>) noexcept : function_info(cv_qualifier::Const, ref_qualifier::lvalue, true) {}
		constexpr function_info(type_t<R(P...) volatile& noexcept>) noexcept : function_info(cv_qualifier::Volatile, ref_qualifier::lvalue, true) {}
		constexpr function_info(type_t<R(P...) const volatile& noexcept>) noexcept : function_info(cv_qualifier::const_volatile, ref_qualifier::lvalue, true) {}

		constexpr function_info(type_t<R(P...) && noexcept>) noexcept : function_info(cv_qualifier::none, ref_qualifier::rvalue, true) {}
		constexpr function_info(type_t<R(P...) const&& noexcept>) noexcept : function_info(cv_qualifier::Const, ref_qualifier::rvalue, true) {}
		constexpr function_info(type_t<R(P...) volatile&& noexcept>) noexcept : function_info(cv_qualifier::Volatile, ref_qualifier::rvalue, true) {}
		constexpr function_info(type_t<R(P...) const volatile&& noexcept>) noexcept : function_info(cv_qualifier::const_volatile, ref_qualifier::rvalue, true) {}
	};
}

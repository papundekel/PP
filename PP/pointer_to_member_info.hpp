#pragma once
#include "type_t.hpp"

namespace PP
{
	template <typename Class, typename Member>
	class pointer_to_member_info
	{
	public:
		[[no_unique_address]] type_t<Member> member_type;
		[[no_unique_address]] type_t<Class> class_type;

	public:
		explicit constexpr pointer_to_member_info(PP::type_t<Member Class::*>) noexcept
		{}
	};

	constexpr inline auto get_pointer_to_member_info = [](auto t) { return pointer_to_member_info(t); };
	constexpr inline auto get_pointer_to_member_member_type = [](auto t) { return pointer_to_member_info(t).member_type; };
	constexpr inline auto get_pointer_to_member_class_type = [](auto t) { return pointer_to_member_info(t).class_type; };
}

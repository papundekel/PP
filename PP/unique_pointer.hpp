#pragma once
#include <utility>
#include <memory>

#include "type_t.hpp"

#include "scoped.hpp"
#include "unique.hpp"

#include "pointer_new.hpp"
#include "pointer_new_array.hpp"
#include "pointer_stack.hpp"

#include "remove_cvref.hpp"

namespace PP
{
	namespace detail
	{
		struct unique_pointer_deleter
		{
			template <typename Pointer>
			constexpr void operator()(const unique<Pointer>& ptr) const // TODO noexcept(?)
			{
				ptr.inner().destroy();
			}
		};
	}

	template <typename Pointer>
	class unique_pointer
	{
		template <typename P>
		friend class unique_pointer;

		scoped<unique<Pointer>, detail::unique_pointer_deleter> ptr;

	public:
		template <typename PointerOther>
		requires (remove_cvref(type_v<PointerOther>)->Template != template_v<unique_pointer>)
		explicit constexpr unique_pointer(const PointerOther& ptr)
			: ptr(ptr)
		{}

		template <typename PointerOther>
		constexpr unique_pointer(unique_pointer<PointerOther>&& other)
			: ptr(std::move(other).ptr)
		{}

		template <typename PointerOther>
		constexpr unique_pointer(const unique_pointer<PointerOther>&) = delete;
		
		constexpr auto get() const noexcept
		{
			return ptr.inner().inner().get_ptr();
		}

		constexpr auto release() noexcept
		{
			return ptr.inner().release();
		}

		constexpr explicit operator bool() const noexcept
		{
			return get();
		}

		constexpr auto& operator*() const noexcept
		{
			return *get();
		}
		constexpr auto operator->() const noexcept
		{
			return get();
		}

		constexpr decltype(auto) operator[](std::size_t index) const noexcept
		{
			return get()[index];
		}
	};
	template <typename Pointer>
	unique_pointer(const Pointer&) -> unique_pointer<Pointer>;

	constexpr inline struct unique_tag_stack_t		{} unique_tag_stack;
	constexpr inline struct unique_tag_new_t		{} unique_tag_new;
	constexpr inline struct unique_tag_new_array_t	{} unique_tag_new_array;

	constexpr auto make_unique(unique_tag_stack_t, auto type, auto&&... args)
	{
		return unique_pointer(pointer_stack(type, PP_FORWARD(args)...));
	}
	constexpr auto make_unique(unique_tag_new_t, auto type, auto&&... args)
	{
		return unique_pointer(pointer_new(type, PP_FORWARD(args)...));
	}
	constexpr auto make_unique(unique_tag_new_array_t, auto type, std::size_t count)
	{
		return unique_pointer(pointer_new_array(type, count));
	}

	constexpr auto make_unique_copy(unique_tag_stack_t, auto&& value)
	{
		return unique_pointer(pointer_stack(PP::placeholder, PP_FORWARD(value)));
	}
	constexpr auto make_unique_copy(unique_tag_new_t, auto&& value)
	{
		return unique_pointer(pointer_new(PP::placeholder, PP_FORWARD(value)));
	}
}

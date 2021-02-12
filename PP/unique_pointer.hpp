#pragma once
#include "placeholder.hpp"
#include "pointer_new.hpp"
#include "pointer_new_array.hpp"
#include "pointer_stack.hpp"
#include "remove_cvref.hpp"
#include "scoped.hpp"
#include "type_t.hpp"
#include "unique.hpp"

namespace PP
{
	namespace detail
	{
		struct unique_pointer_deleter
		{
			template <typename Pointer>
			constexpr void operator()(const unique<Pointer>& ptr) const
			{
				ptr.inner().destroy();
			}
		};
	}

	template <typename Pointer>
	class unique_pointer
	{
		template <typename>
		friend class unique_pointer;

		scoped<unique<Pointer>, detail::unique_pointer_deleter> ptr;

	public:
		constexpr unique_pointer(placeholder_t, const auto& ptr)
			: ptr(make_unique_default(ptr), detail::unique_pointer_deleter{})
		{}

		template <typename PointerOther>
		constexpr unique_pointer(unique_pointer<PointerOther>&& other)
			: ptr(move(other).ptr)
		{}
		
		template <typename PointerOther>
		constexpr unique_pointer& operator=(unique_pointer<PointerOther>&& other)
		{
			ptr = move(other).ptr;
			return *this;
		}

		template <typename PointerOther>
		constexpr unique_pointer(const unique_pointer<PointerOther>&) = delete;
		template <typename PointerOther>
		constexpr unique_pointer& operator=(const unique_pointer<PointerOther>&) = delete;

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
	unique_pointer(placeholder_t, const Pointer&) -> unique_pointer<Pointer>;

	constexpr inline struct unique_tag_stack_t		{} unique_tag_stack;
	constexpr inline struct unique_tag_new_t		{} unique_tag_new;
	constexpr inline struct unique_tag_new_array_t	{} unique_tag_new_array;

	constexpr auto make_unique_pointer(unique_tag_stack_t, concepts::type auto t, auto&&... args)
	{
		return unique_pointer(placeholder, make_pointer_stack(t, PP_FORWARD(args)...));
	}
	constexpr auto make_unique_pointer(unique_tag_new_t, concepts::type auto t, auto&&... args)
	{
		return unique_pointer(placeholder, pointer_new(t, PP_FORWARD(args)...));
	}
	constexpr auto make_unique_pointer(unique_tag_new_array_t, concepts::type auto t, std::size_t count)
	{
		return unique_pointer(placeholder, pointer_new_array(count, t));
	}

	constexpr auto make_unique_copy(auto tag, auto&& value)
	{
		return make_unique_pointer(tag, ~PP_DECLTYPE(value), PP_FORWARD(value));
	}
}

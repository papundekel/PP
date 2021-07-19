#pragma once
#include "always_false.hpp"
#include "apply_template.hpp"
#include "movable.hpp"
#include "placeholder.hpp"
#include "pointer_allocate.hpp"
#include "pointer_new.hpp"
#include "pointer_new_array.hpp"
#include "remove_cvref.hpp"
#include "scoped.hpp"
#include "size_t.hpp"
#include "template_t.hpp"
#include "type_t.hpp"

namespace PP
{
	namespace detail
	{
		struct unique_pointer_deleter
		{
			constexpr void operator()(auto& wrapped_ptr) const
			{
				auto& ptr = wrapped_ptr[tags::o];

				ptr.deallocate();
				ptr = nullptr;
			}
		};
	}

	template <typename Pointer>
	class unique_pointer
	{
		template <typename>
		friend class unique_pointer;

		scoped<movable<Pointer, nullptr_releaser>,
		       detail::unique_pointer_deleter>
			p;

	public:
		unique_pointer() = default;

		constexpr unique_pointer(decltype(nullptr)) noexcept
			: unique_pointer()
		{}

		constexpr unique_pointer(placeholder_t, auto&&... args)
			: p(scoped_default_destructor_tag,
		        movable_default_releaser_tag,
		        PP_F(args)...)
		{}

		constexpr unique_pointer(unique_pointer&& other) = default;
		template <typename PointerOther>
		constexpr unique_pointer(unique_pointer<PointerOther>&& other)
			: p(move(other).p)
		{}

		constexpr unique_pointer& operator=(unique_pointer&& other) = default;
		template <typename PointerOther>
		constexpr unique_pointer& operator=(
			unique_pointer<PointerOther>&& other)
		{
			p = move(other).p;
			return *this;
		}

		unique_pointer(const unique_pointer&) = delete;
		unique_pointer& operator=(const unique_pointer&) = delete;
		template <typename PointerOther>
		unique_pointer(const unique_pointer<PointerOther>&) = delete;
		template <typename PointerOther>
		unique_pointer& operator=(const unique_pointer<PointerOther>&) = delete;

		constexpr auto& get_object() noexcept
		{
			return p[tags::o][tags::o];
		}
		constexpr auto& get_object() const noexcept
		{
			return p[tags::o][tags::o];
		}
		constexpr auto& operator[](tags::o_t) noexcept
		{
			return get_object();
		}
		constexpr auto& operator[](tags::o_t) const noexcept
		{
			return get_object();
		}

		constexpr auto get() const noexcept
		{
			return get_object()[tags::p];
		}

		constexpr auto release() noexcept
		{
			return p[tags::o].release()[tags::p];
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

		constexpr decltype(auto) operator[](size_t index) const noexcept
		{
			return get()[index];
		}
	};

	constexpr inline struct unique_tag_new_t
	{
	} unique_tag_new;
	constexpr inline struct unique_tag_new_array_t
	{
	} unique_tag_new_array;
	constexpr inline struct unique_tag_allocate_t
	{
	} unique_tag_allocate;

	namespace detail
	{
		constexpr auto make_unique_pointer_template(auto tag)
		{
			constexpr auto tag_t = PP_DECLTYPE(tag);

			if constexpr (tag_t == type<unique_tag_new_t>)
				return Template<pointer_new>;
			else if constexpr (tag_t == type<unique_tag_new_array_t>)
				return Template<pointer_new_array>;
			else if constexpr (tag_t == type<unique_tag_allocate_t>)
				return Template<pointer_allocate>;
			else
				static_assert(always_false<decltype(tag)>, "invalid tag type");
		}
		constexpr auto make_unique_pointer_get_maker_helper(auto tag)
		{
			if constexpr (PP_DECLTYPE(tag) == type<unique_tag_new_t>)
				return [](concepts::type auto t, auto&&... args)
				{
					return PP_GT(t)::create(PP_F(args)...);
				};
			else
				return [](concepts::type auto t, auto&&... args)
				{
					return t(PP_F(args)...);
				};
		}
		constexpr auto make_unique_pointer_get_maker(auto tag)
		{
			return [tag](concepts::type auto t, auto&&... args)
			{
				return make_unique_pointer_get_maker_helper(
					tag)(make_unique_pointer_template(tag)(t), PP_F(args)...);
			};
		}
		constexpr auto make_unique_pointer_helper(auto&& maker,
		                                          concepts::type auto t,
		                                          auto&&... args)
		{
			auto p = PP_F(maker)(t, PP_F(args)...);
			return Template<unique_pointer>(PP_DECLTYPE(p))(placeholder,
			                                                move(p));
		}
	}

	constexpr auto make_unique_pointer(auto tag,
	                                   concepts::type auto t,
	                                   auto&&... args)
	{
		return detail::make_unique_pointer_helper(
			detail::make_unique_pointer_get_maker(tag),
			t,
			PP_F(args)...);
	}

	constexpr auto make_unique_copy(auto tag, auto&& value)
	{
		return make_unique_pointer(tag, ~PP_DECLTYPE(value), PP_F(value));
	}
}

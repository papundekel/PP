#pragma once
#include "always_false.hpp"
#include "apply_template.hpp"
#include "placeholder.hpp"
#include "pointer_allocate.hpp"
#include "pointer_new.hpp"
#include "pointer_new_array.hpp"
#include "remove_cvref.hpp"
#include "scoped.hpp"
#include "size_t.hpp"
#include "template_t.hpp"
#include "type_t.hpp"
#include "unique.hpp"

namespace PP
{
	namespace detail
	{
		struct unique_pointer_deleter
		{
			constexpr void operator()(auto& ptr) const
			{
				ptr.get_object().deallocate();
				[[maybe_unused]] auto x = PP::move(ptr);
			}
		};
	}

	template <typename Pointer>
	class unique_pointer
	{
		template <typename>
		friend class unique_pointer;

		scoped<unique<Pointer>, detail::unique_pointer_deleter> p;

	public:
		unique_pointer() = default;

		constexpr unique_pointer(decltype(nullptr)) noexcept
			: unique_pointer()
		{}

		constexpr unique_pointer(placeholder_t, auto&&... args)
			: p(scoped_default_destructor_tag,
				unique_default_releaser_tag,
				PP_FORWARD(args)...)
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

		template <typename PointerOther>
		unique_pointer(const unique_pointer<PointerOther>&) = delete;
		template <typename PointerOther>
		unique_pointer& operator=(const unique_pointer<PointerOther>&) = delete;

		constexpr auto& get_object() noexcept
		{
			return p.get_object().get_object();
		}
		constexpr auto& get_object() const noexcept
		{
			return p.get_object().get_object();
		}

		constexpr auto get() const noexcept
		{
			return get_object().get_ptr();
		}

		constexpr auto release() noexcept
		{
			return p.get_object().release().get_ptr();
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
					return PP_GET_TYPE(t)::create(PP_FORWARD(args)...);
				};
			else
				return [](concepts::type auto t, auto&&... args)
				{
					return t(PP_FORWARD(args)...);
				};
		}
		constexpr auto make_unique_pointer_get_maker(auto tag)
		{
			return [tag](concepts::type auto t, auto&&... args)
			{
				return make_unique_pointer_get_maker_helper(tag)(
					make_unique_pointer_template(tag)(t), PP_FORWARD(args)...);
			};
		}
		constexpr auto make_unique_pointer_helper(auto&&			  maker,
												  concepts::type auto t,
												  auto&&... args)
		{
			auto p = PP_FORWARD(maker)(t, PP_FORWARD(args)...);
			return Template<unique_pointer>(PP_DECLTYPE(p))(placeholder,
															move(p));
		}
	}

	constexpr auto make_unique_pointer(auto				   tag,
									   concepts::type auto t,
									   auto&&... args)
	{
		return detail::make_unique_pointer_helper(
			detail::make_unique_pointer_get_maker(tag), t, PP_FORWARD(args)...);
	}

	constexpr auto make_unique_copy(auto tag, auto&& value)
	{
		return make_unique_pointer(tag, ~PP_DECLTYPE(value), PP_FORWARD(value));
	}
}

#pragma once
#include "apply_template_pack.hpp"
#include "construct_at_pack.hpp"
#include "construct_pack.hpp"
#include "static_block.hpp"

namespace PP
{
	constexpr inline struct nullopt_t {} nullopt{};

	template <typename T>
	class optional
	{
		friend struct optional_creator;

		static_block<T, 1> block;
		bool valid;

	public:
		constexpr optional(nullopt_t) noexcept
			: block()
			, valid(false)
		{}

		constexpr optional(const optional& other)
			: block()
			, valid(other)
		{
			if (other)
				construct(*other);
		}
		
		constexpr optional(optional&& other)
			: block()
			, valid(other)
		{
			if (other)
				construct(*move(other));
		}

		constexpr ~optional()
		{
			reset();
		}

	private:
		constexpr optional(placeholder_t, auto&&... args)
			: block()
			, valid(true)
		{
			construct(PP_FORWARD(args)...);
		}

	public:
		static constexpr auto create(auto&&... args)
		{
			return optional(placeholder, PP_FORWARD(args)...);
		}
	
		constexpr explicit operator bool() const noexcept
		{
			return valid;
		}

		constexpr T& operator*() & noexcept
		{
			return *get_ptr();
		}
		constexpr T&& operator*() && noexcept
		{
			return move(*get_ptr());
		}
		constexpr const T& operator*() const& noexcept
		{
			return *get_ptr();
		}
		constexpr const T&& operator*() const&& noexcept
		{
			return move(*get_ptr());
		}

		constexpr T* operator->() noexcept
		{
			return get_ptr();
		}
		constexpr const T* operator->() const noexcept
		{
			return get_ptr();
		}

		constexpr void emplace(auto&&... args)
		{
			destroy();

			construct(PP_FORWARD(args)...);

			valid = true;
		}

		constexpr void reset()
		{
			destroy();

			valid = false;
		}

	private:
		constexpr T* get_ptr()
		{
			return block.begin();
		}
		constexpr const T* get_ptr() const
		{
			return block.begin();
		}

		constexpr void destroy()
		{
			if (valid)
				get_ptr()->~T();
		}

		constexpr void construct(auto&&... args)
		{
			construct_at_pack(get_ptr(), PP_FORWARD(args)...);
		}
	};

	PP_FUNCTOR(make_optional_copy, auto&& arg)
	{
		return optional<PP_GET_TYPE(~PP_DECLTYPE(arg))>::create(PP_FORWARD(arg));
	});
}

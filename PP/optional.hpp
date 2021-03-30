#pragma once

namespace PP
{
	constexpr inline struct nullopt_t {} nullopt{};

	template <typename T>
	class optional
	{
		alignas(T) char buffer[sizeof(T)];
		[[no_unique_address]] T* ptr;

	public:
		constexpr optional(nullopt_t) noexcept
			: buffer()
			, ptr(nullptr)
		{}
		constexpr optional(auto&&... args)
			: buffer()
			, ptr(new (buffer) T(PP_FORWARD(args)...))
		{}

		constexpr explicit operator bool() const noexcept
		{
			return ptr != nullptr;
		}

		constexpr T& operator*() noexcept
		{
			return *ptr;
		}
		constexpr const T& operator*() const noexcept
		{
			return *ptr;
		}
		constexpr T* operator->() noexcept
		{
			return ptr;
		}
		constexpr const T* operator->() const noexcept
		{
			return ptr;
		}

		constexpr ~optional()
		{
			if (ptr)
				ptr->~T();
			ptr = nullptr;
		}
	};
}

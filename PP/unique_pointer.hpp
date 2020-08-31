#pragma once
#include <utility>
#include <memory>
#include "scoped.hpp"
#include "unique.hpp"

namespace Papo
{
	namespace detail
	{
		template <typename T>
		struct default_deleter
		{
			constexpr void operator()(const unique<T*>& u) const
			{
				delete u.get();
			}
		};
		template <typename T>
		struct default_deleter<T[]>
		{
			constexpr void operator()(const unique<T*>& u) const
			{
				delete[] u.get();
			}
		};
	}

	template <typename T, typename Deleter = detail::default_deleter<T>>
	class unique_pointer
	{
		using ptr_base_t = std::conditional_t<std::is_array_v<T>, std::remove_extent_t<T>, T>;

		scoped<unique<ptr_base_t*>, Deleter> x;

	public:
		constexpr unique_pointer() = default;
		constexpr unique_pointer(ptr_base_t* ptr) noexcept
			: x(ptr)
		{}
		template <typename D>
		constexpr unique_pointer(ptr_base_t* ptr, D&& deleter) noexcept
			: x(ptr, std::forward<D>(deleter))
		{}
		constexpr unique_pointer(unique_pointer&& other)
			= default;
		constexpr unique_pointer& operator=(unique_pointer&& other)
			= default;

		constexpr ptr_base_t* get() const noexcept
		{
			return x.get().get();
		}

		constexpr auto& get_deleter() const noexcept
		{
			return x.get_destructor();
		}

		constexpr auto release() noexcept
		{
			return x.get().release();
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
}

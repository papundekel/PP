#pragma once
#include <utility>
#include <memory>
#include "compressed_pair.hpp"
#include "unique_raw_pointer.hpp"

namespace Papo
{
	template <typename T, typename Deleter = std::default_delete<T>>
	class unique_pointer
	{
		using ptr_base_t = std::conditional_t<std::is_array_v<T>, std::remove_extent_t<T>, T>;

		compressed_pair<unique_raw_pointer<ptr_base_t>, Deleter> p;

		constexpr void delete_ptr() noexcept
		{
			if (get())
				get_deleter()(get());
		}

	public:
		constexpr unique_pointer() noexcept
			: p{ nullptr, {} }
		{}
		constexpr unique_pointer(ptr_base_t* ptr) noexcept
			: p{ ptr, {} }
		{}
		template <typename D>
		constexpr unique_pointer(ptr_base_t* ptr, D&& deleter) noexcept
			: p{ ptr, std::forward<D>(deleter) }
		{}
		constexpr unique_pointer(unique_pointer&& other)
			= default;
		constexpr ~unique_pointer()
		{
			delete_ptr();
		}
		constexpr auto& operator=(unique_pointer&& other) noexcept
		{
			delete_ptr();
			p = std::move(other.p);
			return *this;
		}

		constexpr ptr_base_t* get() const noexcept
		{
			return p.first.get();
		}

		constexpr auto& get_deleter() const noexcept
		{
			return p.second;
		}

		constexpr auto release() noexcept
		{
			return std::move(p.first);
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

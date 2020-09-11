#pragma once
#include "compressed_pair.hpp"
#include "different_cvref.hpp"
#include "placeholder.hpp"

namespace PP
{
	template <typename T, typename Destructor>
	class scoped
	{
		compressed_pair<T, Destructor> pair;

	public:
		constexpr scoped() = default;

		constexpr scoped(const scoped&) = default;
		constexpr scoped(scoped&&) = default;

		constexpr scoped& operator=(const scoped&) = default;

		constexpr T& get()
		{
			return pair.first;
		}
		constexpr const T& get() const
		{
			return pair.first;
		}
		constexpr Destructor& get_destructor()
		{
			return pair.second;
		}
		constexpr const Destructor& get_destructor() const
		{
			return pair.second;
		}
	private:
		constexpr void destroy()
		{
			get_destructor()(get());
		}
	public:
		constexpr scoped& operator=(scoped&& other)
		{
			destroy();
			pair = std::move(other).pair;
			return *this;
		}

		constexpr ~scoped()
		{
			destroy();
		}

		template <different_cvref<scoped> U>
		constexpr scoped(U&& value)
			: pair{ std::forward<U>(value), {} }
		{}
		template <different_cvref<scoped> U, typename D>
		constexpr scoped(U&& value, D&& destructor)
			: pair{ std::forward<U>(value), std::forward<D>(destructor) }
		{}
		template <typename D>
		constexpr scoped(placeholder, D&& destructor)
			: pair{ {}, std::forward<D>(destructor) }
		{}
	};
}

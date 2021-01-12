#pragma once
#include "compressed_pair.hpp"
#include "placeholder.hpp"

namespace PP
{
	template <typename T, typename Destructor>
	class scoped;
	
	namespace detail
	{
		template <typename T>
		constexpr inline bool is_scoped = false;
		template <typename T, typename Destructor>
		constexpr inline bool is_scoped<scoped<T, Destructor>> = true;
	}

	template <typename T, typename Destructor>
	class scoped
	{
		template <typename U, typename D>
		friend class scoped;

		compressed_pair<T, Destructor> pair;

	public:
		constexpr scoped() = default;

		template <typename U, typename D>
		constexpr scoped(const scoped<U, D>& other)
			: pair(other.pair.first, other.pair.second)
		{}
		template <typename U, typename D>
		constexpr scoped(scoped<U, D>&& other)
			: pair(std::move(other).pair.first, std::move(other).pair.second)
		{}

		constexpr scoped& operator=(const scoped&) = default;

		constexpr T& inner()
		{
			return pair.first;
		}
		constexpr const T& inner() const
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
			get_destructor()(inner());
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

		template <typename U>
		requires (!detail::is_scoped<std::remove_cvref_t<U>>)
		constexpr scoped(U&& value)
			: pair(std::forward<U>(value), {})
		{}
		template <typename U, typename D>
		requires (!detail::is_scoped<std::remove_cvref_t<U>>)
		constexpr scoped(U&& value, D&& destructor)
			: pair(std::forward<U>(value), std::forward<D>(destructor))
		{}
		template <typename D>
		constexpr scoped(placeholder_t, D&& destructor)
			: pair({}, std::forward<D>(destructor))
		{}
	};
}

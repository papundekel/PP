#pragma once
#include <type_traits>

namespace PP
{
	namespace detail
	{
		template <typename T>
		struct reference_wrapper
		{
			T* ptr;

			constexpr reference_wrapper(T& ref) noexcept
				: ptr(&ref)
			{}

			constexpr T& get() const noexcept
			{
				return *ptr;
			}
			constexpr operator T& () const noexcept
			{
				return get();
			}
		};
	}

	template <typename T>
	using reference_wrapper = detail::reference_wrapper<std::remove_reference_t<T>>;

	template <typename T>
	using cref_t = reference_wrapper<const T>;
}

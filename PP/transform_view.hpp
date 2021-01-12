#pragma once
#include "simple_view.hpp"
#include "base.hpp"
#include "get_type.hpp"
#include "apply_template.hpp"
#include "decompose_template.hpp"
#include "apply_transform.hpp"
#include "arrow_operator_wrapper.hpp"
#include "remove_cvref.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T>
		struct transform_iterator_pointer_base
		{
			T ptr;
		};

		constexpr auto&& transform_iterator_base_get(auto&& i) noexcept
		{
			if constexpr PP_DECLTYPE(i)->Template == template_v<transform_iterator_pointer_base>)
				return i.ptr;
			else
				return PP_FORWARD(i);
		}

		constexpr inline auto x = [](auto t)
		{
			if constexpr (-template_v<std::is_pointer>[t])
				return template_v<transform_iterator_pointer_base>[t];
			else
				return t;
		};

		template <typename Transform>
		using transform_iterator_base_t = apply_transform_t<x, Transform>;
	}

	template <typename BaseIterator, typename Transform>
	class transform_iterator : public detail::transform_iterator_base_t<BaseIterator>, public detail::transform_iterator_base_t<Transform>
	{
		using IteratorBase = detail::transform_iterator_base_t<BaseIterator>;
		using TransformBase = detail::transform_iterator_base_t<Transform>;

	public:
		constexpr transform_iterator(BaseIterator i, Transform&& t)
			: IteratorBase(i)
			, TransformBase(std::move(t))
		{}
		constexpr transform_iterator(BaseIterator i, const Transform& t)
			: IteratorBase(i)
			, TransformBase(t)
		{}

		constexpr decltype(auto) operator*() const
		{
			return detail::transform_iterator_base_get((const TransformBase&)*this)(*base());
		}
		constexpr decltype(auto) operator->() const
		{
			return arrow_operator_wrapper(**this);
		}
		constexpr auto& operator+=(size_t offset)
		{
			base() += offset;
			return *this;
		}
		constexpr auto& operator-=(size_t offset)
		{
			base() -= offset;
			return *this;
		}
		constexpr auto operator==(iterator auto other) const
		{
			return base() == other;
		}
		constexpr auto operator-(const auto& other) const
		{
			return base() - PP::base(other);
		}
		constexpr decltype(auto) operator[](std::size_t index) const
		{
			return this->operator()(base()[index]);
		}
		constexpr BaseIterator& base()
		{
			return detail::transform_iterator_base_get((IteratorBase&)*this);
		}
		constexpr const BaseIterator& base() const
		{
			return detail::transform_iterator_base_get((const IteratorBase&)*this);
		}
	};

	template <typename Functor>
	struct transform
	{
		Functor functor;
	};

	template <typename F>
	constexpr view auto transform_view(view auto&& v, F&& f)
	{
		return transform_iterator(begin(v), std::forward<F>(f)) ^ transform_iterator(end(v), std::forward<F>(f));
	}

	constexpr iterator auto operator&(iterator auto i, transform<auto> t)
	{
		return transform_iterator(i, std::move(t).functor);
	}

	template <view View>
	constexpr view auto operator||(View&& v, transform<auto> t)
	{
		return begin(std::forward<View>(v)) & std::move(t) ^ end(std::forward<View>(v));
	}

	template <view View>
	constexpr view auto operator|(View&& v, transform<auto> t)
	{
		return transform_view(std::forward<View>(v), std::move(t).functor);
	}
}

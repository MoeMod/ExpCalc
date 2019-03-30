//
// Created by 小白白 on 2019-02-15.
//

#ifndef EXPCALC_CONSTANT_H
#define EXPCALC_CONSTANT_H

#include "IConstant.h"
#include "ctype.h"

namespace detail
{
	template<class T, class Final>
	class CConstantVisitorGenerator;
	template<template<class...> class List, class First, class...TypesToMake, class Final>
	class CConstantVisitorGenerator<List<First, TypesToMake...>, Final> : public CConstantVisitorGenerator<List<TypesToMake...>, Final>
	{
	public:
		// CRTP Generator
		// known *this, unknown rhs
		bool equalsTo(const IConstant &rhs) const override { return rhs.rightEqualsTo(static_cast<const Final &>(*this)); }
		std::shared_ptr<IConstant> add(const IConstant &rhs) const override { return rhs.rightAdd(static_cast<const Final &>(*this)); }
		std::shared_ptr<IConstant> multiply(const IConstant &rhs) const override { return rhs.rightMultiply(static_cast<const Final &>(*this)); }
		// static dispatch
		bool rightEqualsTo(const TConstant<First> &lhs) const override
		{
			const auto &rhs = static_cast<const Final &>(*this);
			return lhs.get() == rhs.get();
		}
		std::shared_ptr<IConstant> rightAdd(const TConstant<First> &lhs) const override
		{
			const auto &rhs = static_cast<const Final &>(*this);
			return std::make_shared<TConstant<typename std::common_type<typename Final::type, First>::type>>(lhs.get() + rhs.get());
		}
		std::shared_ptr<IConstant> rightMultiply(const TConstant<First> &lhs) const override
		{
			const auto &rhs = static_cast<const Final &>(*this);
			return std::make_shared<TConstant<typename std::common_type<typename Final::type, First>::type>>(lhs.get() * rhs.get());
		}
	};
	template<template<class...> class List, class Final>
	class CConstantVisitorGenerator<List<>, Final> : public IConstant {};
}

namespace detail
{
	template<class T>
	std::string toString(T &&v)
	{
		std::string ret = std::to_string(std::forward<T>(v));
		if(!ret.empty() && (
				!isdigit(ret.front()) ||
				!isdigit(ret.back())
				))
		{
			ret = '(' + std::move(ret) + ')';
		}
		return ret;
	}

	template<class T>
	bool isZero(T &&v)
	{
		return std::forward<T>(v)==0;
	}

	template<class T>
	bool isOne(T &&v)
	{
		return std::forward<T>(v)==1;
	}
}

template<class T>
class TConstant : public detail::CConstantVisitorGenerator<ConstantTypeList, TConstant<T>>
{
public:
	using type = T;

public:
	explicit TConstant(T v) : value(std::move(v)) {}

public:
	std::string toString() const override { return detail::toString(value); }
	std::shared_ptr<IExpression> simplify() override { return IExpression::shared_from_this(); }

	bool isZero() const override { return detail::isZero(value); }
	bool isOne() const override { return detail::isOne(value); }
	std::shared_ptr<IConstant> invert() const override { return std::make_shared<TConstant<T>>(-get()); }

public:
	const T& get() const { return value; }

protected:
	T value;
};

#endif //EXPCALC_CONSTANT_H

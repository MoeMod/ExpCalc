//
// Created by 小白白 on 2019-02-15.
//

#ifndef EXPCALC_CONSTANT_H
#define EXPCALC_CONSTANT_H

#include "IConstant.h"

namespace detail
{
	template<class T, class Final>
	class CConstantVisitorGenerator;
	template<template<class...> class List, class First, class...TypesToMake, class Final>
	class CConstantVisitorGenerator<List<First, TypesToMake...>, Final> : public CConstantVisitorGenerator<List<TypesToMake...>, Final>
	{
	public:
		// CRTP Generator
		bool equalsTo(const IConstant &rhs) const override
		{
			// known *this, unknown rhs
			return rhs.rightEqualsTo(static_cast<const Final &>(*this));
		}
		bool rightEqualsTo(const TConstant<First> &lhs) const override
		{
			// static dispatch
			const auto &rhs = static_cast<const Final &>(*this);
			return lhs.get() == rhs.get();
		}
	};
	template<template<class...> class List, class Final>
	class CConstantVisitorGenerator<List<>, Final> : public IConstant {};
}

template<class Final>
using TConstantVisitor = detail::CConstantVisitorGenerator<ConstantTypeList, Final>;

namespace detail
{
	template<class T>
	std::string toString(T &&v)
	{
		std::string ret = std::to_string(std::forward<T>(v));
		if(!ret.empty() && (
				!std::isdigit(ret.front()) ||
				!std::isdigit(ret.back())
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
class TConstant : public TConstantVisitor<TConstant<T>>
{
public:
	explicit TConstant(T v) : value(std::move(v)) {}

public:
	std::string toString() const override { return detail::toString(value); }

	bool isZero() const override { return detail::isZero(value); }
	bool isOne() const override { return detail::isOne(value); }

//	bool equalsTo(const IConstant &rhs) const override
//	{
//		return rhs.rightEqualsTo(*this);
//	}
//	bool rightEqualsTo(const TConstant<int> &lhs) const override { return lhs.get() == this->get(); }
//	bool rightEqualsTo(const TConstant<long> &lhs) const override { return lhs.get() == this->get(); }
//	bool rightEqualsTo(const TConstant<long long> &lhs) const override { return lhs.get() == this->get(); }
//	bool rightEqualsTo(const TConstant<unsigned long> &lhs) const override { return lhs.get() == this->get(); }
//	bool rightEqualsTo(const TConstant<unsigned long long> &lhs) const override { return lhs.get() == this->get(); }
//	bool rightEqualsTo(const TConstant<float> &lhs) const override { return lhs.get() == this->get(); }
//	bool rightEqualsTo(const TConstant<double> &lhs) const override { return lhs.get() == this->get(); }
//	bool rightEqualsTo(const TConstant<long double> &lhs) const override { return lhs.get() == this->get(); }

public:
	const T& get() const { return value; }

protected:
	T value;
};

#endif //EXPCALC_CONSTANT_H
